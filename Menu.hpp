//  ============
    #pragma once
    #include <iostream>
    #include <vector>
    #include "ANN.hpp"
    using std::cin;
    using std::cout;
    using std::endl;
//  ================

//  =====================
    class Menu {

//      ============
//      Custom Types
//      =============================================
        enum MenuChoices  {Quit, Insert, Train, Test, SetLogic};
        enum LogicChoices {Buffer, NOT, AND, NAND, OR, NOR, XOR, XNOR};
//      =============================================

        public:

//      =======================
//      public member functions
//      =======================

//          ===================
//          Default constructor
//          ===================
            Menu(void) {
                userMenuSelection = Quit;
                userLogicSelection = AND;
            } // Default constructor
//          ========================

//          ===========
//          destructor
//          ==============
            ~Menu(void) {}
//          ==============

//          ===
//          Get
//          ===================
            MenuChoices Get() {
                return userMenuSelection;
            } // Get
//          ========

//          ===
//          Set
//          ==============================
            void Set(MenuChoices choice) {
                userMenuSelection = choice;
            } // Set
//          ========

//          =======
//          MenuDisplay
//          ================
            void MenuDisplay() {
                cout << "+-----------------------------+" << endl;
                cout << "|           Options           |" << endl;
                cout << "+-----------------------------+" << endl;
                cout << "| 1:  Quit        2:  Insert  |" << endl;
                cout << "| 3:  Train       4:  Test    |" << endl;
                cout << "| 5:  Set Logic               |" << endl;
                cout << "+-----------------------------+" << endl;
            } // Display
//          ============

//          ============
//          LogicDisplay
//          =====================
            void LogicDisplay() {
                cout << "+-----------------------------+" << endl;
                cout << "|           Options           |" << endl;
                cout << "+-----------------------------+" << endl;
                cout << "| 1:  Buffer      2:  NOT     |" << endl;
                cout << "| 3:  AND         4:  NAND    |" << endl;
                cout << "| 5:  OR          6:  NOR     |" << endl;
                cout << "| 7:  XOR         8:  XNOR    |" << endl;
                cout << "+-----------------------------+" << endl;
            } // LogicDisplay
//          =================

//          ===================
//          printCurrentLogic()
//          ==========================
            void printCurrentLogic(ANN &ann) {

                vector<float> truthTable = ann.returnTruthTable();
                
                cout << "+-----------------------------+" << endl;
                cout << "|     Logic Operator: ";          
                switch (userLogicSelection) {
                    case Buffer: 
                        cout << "Buffer  |" << endl;
                        break;
                    case NOT:
                        cout << "NOT     |" << endl;
                        break;
                    case AND:
                        cout << "AND     |" << endl;
                        break;
                    case NAND:
                        cout << "NAND    |" << endl;
                        break;
                    case OR:
                        cout << "OR      |" << endl;
                        break;
                    case NOR:
                        cout << "NOR     |" << endl;
                        break;
                    case XOR:
                        cout << "XOR     |" << endl;
                        break;
                    case XNOR:
                        cout << "XNOR    |" << endl;
                        break;
                    default:
                        cout << "UNKNOWN |" << endl;
                        break;
                }
                cout << "+-----------------------------+" << endl;
                cout << "|         Truth Table         |" << endl;
                cout << "+-----------------------------+" << endl;
                cout << "|                             |" << endl;
                cout << "|             0  1            |" << endl;
                cout << "|             ----            |" << endl;
                cout << "|         0 | ";
                for (int i = 0; i < 2; i++) {
                    cout << truthTable[i] << "  ";
                }
                cout << "          |" << endl;
                cout << "|         1 | ";
                for (int i = 2; i < 4; i++) {
                    cout << truthTable[i] << "  ";
                }
                cout << "          |" << endl;
                cout << "|                             |" << endl;
            } // printCurrentLogic()
//          ========================

//          =========
//          QueryUser
//          ==================
            void QueryUser(ANN &ann) {
                printCurrentLogic(ann);
                MenuDisplay();
                int selection;

                cout << "Enter menu seelction: ";
                cin >> selection;

                switch (selection) {
                    case 1: userMenuSelection = Quit;
                        break;
                    case 2: userMenuSelection = Insert;
                        break;
                    case 3: userMenuSelection = Train;
                        break;
                    case 4: userMenuSelection = Test;
                        break;
                    case 5: userMenuSelection = SetLogic;
                        break;
                    default: userMenuSelection = Quit;
                        break;
                }
                cout << endl;
            } // QueryUser
//          ==============

//          ================
//          QueryUserLogic()
//          =======================
            void QueryUserLogic() {
                LogicDisplay();

                int selection;
                cout << "Enter selection for logic gate: ";
                cin >> selection;
                cout << endl;

                switch (selection) {
                    case 1: userLogicSelection = Buffer;
                        break;
                    case 2: userLogicSelection = NOT;
                        break;
                    case 3: userLogicSelection = AND;
                        break;
                    case 4: userLogicSelection = NAND;
                        break;
                    case 5: userLogicSelection = OR;
                        break;
                    case 6: userLogicSelection = NOR;
                        break;
                    case 7: userLogicSelection = XOR;
                        break;
                    case 8: userLogicSelection = XNOR;
                        break;
                    default: userLogicSelection = AND;
                        break;
                }; // switch
            } // QueryUserLogic()
//          =====================

//          ==============
//          processCommand
//          ==========================================
            void processCommand(ANN &ann) {

                if (userMenuSelection != Quit) {
                    switch (userMenuSelection) {
                        case Insert:
                            int layer;
                            cout << "Choose Layer to insert node: ";
                            cin >> layer;
                            ann.insert(layer, 0);
                            break;
                        case Train:
                            int iterations;
                            cout << "choose number of training iterations: ";
                            cin >> iterations;
                            for (int i = 0; i < iterations; i++) {
                                ann.ForwardPropogation(true);
                            }
                            break;
                        case Test:
                            float bitOne, bitTwo;
                            cout << "Choose bit # one: ";
                            cin >> bitOne;
                            cout << "Choose bit # two: ";
                            cin >> bitTwo;
                            ann.SetInputs(bitOne, bitTwo);
                            ann.ForwardPropogation();
                            break;
                        case SetLogic:
                            int choice;
                            QueryUserLogic();
                            ProcessLogicCommand(ann);
                            break;
                        default:
                            cout << "Invalid selection" << endl;
                            break;
                    }
                }
            } // processCommand
//          ===================

            void ProcessLogicCommand(ANN &ann) {
                vector<float> truthTable;
                switch (userLogicSelection) {
                    case Buffer: 
                        break;
                    case NOT:
                        break;
                    case AND:
                        truthTable = {0, 0, 0, 1};
                        ann.setTruthTable(truthTable);
                        break;
                    case NAND:
                        truthTable = {1, 1, 1, 0};
                        ann.setTruthTable(truthTable);
                        break;
                    case OR:
                        truthTable = {0, 1, 1, 1};
                        ann.setTruthTable(truthTable);
                        break;
                    case NOR:
                        truthTable = {1, 0, 0, 0};
                        ann.setTruthTable(truthTable);
                        break;
                    case XOR:
                        truthTable = {0, 1, 1, 0};
                        ann.setTruthTable(truthTable);
                        break;
                    case XNOR:
                        truthTable = {1, 0, 0, 1};
                        ann.setTruthTable(truthTable);
                        break;
                    default:
                        break;
                }
            }

//          ========
//          Continue
//          =================
            bool Continue() {
                return userMenuSelection != Quit;
            } // Continue
//          =============

        private:

//      ========================
//      private member variables
//      ========================

            MenuChoices userMenuSelection;
            LogicChoices userLogicSelection;

    };
