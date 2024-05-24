    #include <iostream>
    #include <vector>
    #include <cmath>
    #include <random>
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

            ANN(void) {
                learningRate = 0.1;
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
                }
                
            }

            void ForwardPropogation(string backPass) {

                inputs[0]->value = round(randomNum());

                vector<float> expectedValues;
                if (inputs[0]->value == 1) {
                    expectedValues.push_back(1);
                    expectedValues.push_back(0);
                } else {
                    expectedValues.push_back(0);
                    expectedValues.push_back(1);
                }

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
                cout << round(current->value) << " --> " << expectedValues[0] << "  " << expectedValues[1] << endl;
                if (backPass == "backPass")
                    BackPropagation(current, expectedValues);
            }

            void BackPropagation(Node* firstOutput, vector<float> expectedValues) {

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

            void printANN() {
                for (auto node : inputs) {
                    cout << node->value << "   ";
                }
                cout << endl;
                Node* current = inputs[0];
                while (current->frontPtrs.size() > 0) {
                    for (auto node : current->frontPtrs) {
                        cout << node->value << "   ";
                    }
                    cout << endl;
                    current = current->frontPtrs[0];
                }
            }

            void printMSE(float value, float expected) {
                float error = 0.5 * pow(value - expected, 2);
                cout << error << endl;
            }

            vector<float> ExpectedValues() {

            }

            float randomNum() {
                random_device rd;
                mt19937 gen(rd());
                uniform_real_distribution<float> dis(0.0, 1.0);
                return dis(gen);
            }

        private:

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
                Node* current = inputs[0];
                while (current->frontPtrs.size() > 0) {
                    current = current->frontPtrs[0];
                }
                while (current->backPtrs.size() > 0) {
                    current = current->backPtrs[0];
                    for (auto node : current->frontPtrs) {
                        node = NULL;
                        delete node;
                    }
                }
                for (auto node : inputs) {
                    node = NULL;
                    delete node;
                }
            }

            vector<Node*> inputs;
            float learningRate;

        };
