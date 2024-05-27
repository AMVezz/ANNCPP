    #pragma once
    #include <iostream>
    #include <vector>
    #include <cmath>
    #include <random>
    #include <set>
    #include <stack>
    using namespace std;
    
    class ANN {

        struct Node {
            float value;
            float bias;
            vector<float> weights;
            vector<Node*> frontPtrs;
            vector<Node*> backPtrs;
            float errorTerm;
        };

        public:

//      =======================
//      Public member Functions
//      =======================

            ANN(void) {
                learningRate = 0.1;
                truthTable = {0, 0, 0, 0};
                trainingIterations = 0;
                allGates = true;
            }
            ~ANN(void) {
                destroy();
            }

            void insert(int layer, float value) {

                Node* newNode = new Node;
                newNode->value = value;
                newNode->bias = 0.1;
                if (layer == 1) {
                    inputs.push_back(newNode);
                    for (auto node : inputs[0]->frontPtrs) {
                        node->backPtrs.push_back(newNode);
                        newNode->frontPtrs.push_back(node);
                    }
                } else if (layer == 2) {
                    for (auto node : inputs) {
                        node->frontPtrs.push_back(newNode);
                        newNode->backPtrs.push_back(node);
                        newNode->weights.push_back(randomNum());
                    }
                    if (inputs[0]->frontPtrs[0]->frontPtrs.size() > 0) {
                        for (auto node : inputs[0]->frontPtrs[0]->frontPtrs) {
                            node->backPtrs.push_back(newNode);
                            node->weights.push_back(randomNum());
                            newNode->frontPtrs.push_back(node);
                        }
                    }
                } else {
                    Node* current = inputs[0];
                    for (int i = 0; i < layer - 3; i++) {
                        current = current->frontPtrs[0];
                    }
                    for (auto node : current->frontPtrs) {
                        node->frontPtrs.push_back(newNode);
                        newNode->backPtrs.push_back(node);
                        newNode->weights.push_back(randomNum());
                    }
                    if (current->frontPtrs[0]->frontPtrs[0]->frontPtrs.size() > 0) {
                        for (auto node : current->frontPtrs[0]->frontPtrs[0]->frontPtrs) {
                            node->backPtrs.push_back(newNode);
                            node->weights.push_back(randomNum());
                            newNode->frontPtrs.push_back(node);
                        }
                    }
                }
                
            }

            void deleteNode(int layer) {

                if (layer == 1) {
                    delete inputs[inputs.size() - 1];
                    for (auto node : inputs[0]->frontPtrs) {
                        node->backPtrs.pop_back();
                        node->weights.pop_back();
                    }
                } else if (layer == 2) {
                    delete inputs[0]->frontPtrs[inputs[0]->frontPtrs.size() - 1];
                    for (auto node : inputs) {
                        node->frontPtrs.pop_back();
                    }
                    if (inputs[0]->frontPtrs[0]->frontPtrs.size() > 0) {
                        for (auto node : inputs[0]->frontPtrs[0]->frontPtrs) {
                            node->backPtrs.pop_back();
                            node->weights.pop_back();
                        }
                    }
                } else {
                    Node* current = inputs[0];
                    for (int i = 0; i < layer - 3; i++) {
                        current = current->frontPtrs[0];
                    }
                    delete current->frontPtrs[0]->frontPtrs[current->frontPtrs[0]->frontPtrs.size() - 1];
                    for (auto node : current->frontPtrs) {
                        node->frontPtrs.pop_back();
                    }
                    if (current->frontPtrs[0]->frontPtrs[0]->frontPtrs.size() > 0) {
                        for (auto node : current->frontPtrs[0]->frontPtrs[0]->frontPtrs) {
                            node->backPtrs.pop_back();
                            node->weights.pop_back();
                        }
                    }
                }

            }

            void ForwardPropogation(bool backPass = false) {

                inputs[0]->value = round(randomNum());
                inputs[1]->value = round(randomNum());

                if (allGates) {
                    inputs[2]->value = round(randomNum());
                    inputs[3]->value = round(randomNum());
                    inputs[4]->value = round(randomNum());
                    inputs[5]->value = round(randomNum());
                    truthTable = {inputs[2]->value, inputs[3]->value, inputs[4]->value, inputs[5]->value};
                } else {
                    for (int i = 2; i < 6; i++) {
                        inputs[i]->value = truthTable[i-2];
                    }
                }
   
                vector<float> expectedValues = returnExpectedValues();

                Node* current = inputs[0];
                while (current->frontPtrs.size() > 0) {
                    for (auto node : current->frontPtrs) {
                        float value = 0;
                        for (int i = 0; i < node->backPtrs.size(); i++) {
                            value += node->backPtrs[i]->value * node->weights[i];
                        }
                        value += node->bias;
                        value = activation("sigmoid", value);
                        node->value = value;
                    }
                    current = current->frontPtrs[0];
                }

                if (backPass == true)
                    BackPropagation(current, expectedValues);

                checkOutput(current, expectedValues);
            }

            void BackPropagation(Node* firstOutput, vector<float> expectedValues) {

                trainingIterations++;

                Node* current = firstOutput->backPtrs[0];
                Node* temp = current; // so I can go back to output nodes after error terms are found

                float weightGradient;
                float biasGradient;
                
                // find output layer error terms
                for (int i = 0; i < current->frontPtrs.size(); i++) {
                    Node* node = current->frontPtrs[i];
                    node->errorTerm = (node->value - expectedValues[i]) * (node->value * (1 - node->value));
                }

                // find hidden layer error terms
                current = current->backPtrs[0];
                while (current->backPtrs.size() > 1) {
                    for (int i = 0; i < current->frontPtrs.size(); i++) {
                        Node* node = current->frontPtrs[i];
                        node->errorTerm = 0;
                        for (int j = 0; j < node->frontPtrs.size(); j++) {
                            Node* previousNode = node->frontPtrs[j];
                            node->errorTerm += previousNode->errorTerm * previousNode->weights[i];
                        }
                        node->errorTerm *= (node->value * (1 - node->value));
                    }
                    current = current->backPtrs[0];
                }

                // update weights and biases with gradients
                current = temp;
                while (current->backPtrs.size() > 0) {
                    for (auto node : current->frontPtrs) {
                        for (int i = 0; i < node->backPtrs.size(); i++) {
                            weightGradient = node->errorTerm * node->backPtrs[i]->value;
                            node->weights[i] = node->weights[i] - learningRate * weightGradient;
                        }
                        biasGradient = node->errorTerm;
                        node->bias = node->bias - learningRate * biasGradient;
                    }
                    current = current->backPtrs[0];
                }

            }

            void checkOutput(Node* firstOutput, vector<float> expectedValues) {

                bool output = true;
                if (firstOutput->value > firstOutput->backPtrs[0]->frontPtrs[1]->value)
                    output = false;

                bool expected = true;
                if (expectedValues[0] > expectedValues[1])
                    expected = false;

                bool compare = output == expected;
                for (auto bit : truthTable) {
                    cout << bit << " ";
                }
                cout << "| " 
                << inputs[1]->value << " " << inputs[0]->value << " = " << output
                << " | " << compare << " | " << trainingIterations << " | " 
                << returnMSE(firstOutput->value, expectedValues[0]) << endl;

            }
            
            void printANN() {
                                
                Node* current = inputs[0];
                cout << current->value << "  ";

                int i = 0;
                bool iterate = true;
                while (iterate) { 
                    iterate = false;

                    while (current->frontPtrs.size() > 0) {
                        if (current->frontPtrs.size() > i) {
                            current = current->frontPtrs[i];
                            cout << round(current->value * 100)/100 << "  ";
                            iterate = true;
                        } else {
                            current = current->frontPtrs[0];
                            cout << "   ";
                        }
                    }
                    cout << endl;

                    i++;
                    if (inputs.size() > i) {
                        current = inputs[i];
                        cout << round(current->value * 100)/100 << "  ";
                        iterate = true;
                    } else if (iterate){
                        current = inputs[0];
                        cout << "   ";
                    }   
                }
            }

            float returnMSE(float value, float expected) {
                return 0.5 * pow(value - expected, 2);
            }

            vector<float> returnTruthTable() {
                return truthTable;
            }

            void SetInputs(float bitOne, float bitTwo) {
                inputs[0]->value = bitOne;
                inputs[1]->value = bitTwo;
            }

            void setTruthTable(vector<float> truthTable) {
                this->truthTable = truthTable;
            }

            void setAllGates(bool choice) {
                this->allGates = choice;
            }
            
            vector<float> returnExpectedValues() {
                int truthIndex = 0;
                int expectedBit = 0;
                for (int i = 0; i < 2; i++) {
                    truthIndex += inputs[i]->value * (i + 1);
                }
                expectedBit = truthTable[truthIndex];
                if (expectedBit == 0) {
                    return {1, 0};
                }
                return {0, 1};
            }

            float randomNum() {
                random_device rd;
                mt19937 gen(rd());
                uniform_real_distribution<float> dis(0.0, 1.0);
                return dis(gen);
            }

        private:

//      ========================
//      Private Member Functinos
//      ========================

            float activation(string function, float value) {
                if (function == "sigmoid") {
                    return 1 / (1 + exp(-1 * value));
                }
                return value;
            }

            float MeanSquaredError(float value, float expected) {
                return 0.5 * pow(value - expected, 2);
            }

            void destroy() {
                set<Node*> visited;  // To keep track of all visited nodes

                // First collect all nodes in a set to avoid duplicates
                stack<Node*> toVisit;
                for (auto input : inputs) {
                    toVisit.push(input);
                }

                while (!toVisit.empty()) {
                    Node* current = toVisit.top();
                    toVisit.pop();
                    if (visited.find(current) == visited.end()) {  // Ensure each node is only visited once
                        visited.insert(current);
                        for (auto& front : current->frontPtrs) {
                            toVisit.push(front);
                        }
                    }
                }

                // Now delete all collected nodes
                for (auto node : visited) {
                    delete node;
                }

                inputs.clear();  // Clear the inputs vector
            }

//       ========================
//       Private Member Variables
//       ========================

            vector<float> truthTable;
            vector<Node*> inputs;
            float learningRate;
            double trainingIterations;
            bool allGates;
        };
