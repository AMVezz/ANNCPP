
//  ============
    #pragma once
    #include <iostream>
    #include <vector>
    #include "ANN.hpp"
    using std::cin;
    using std::cout;
    using std::endl;
//  ================

//  ============
    class Menu {

//      ============
//      Custom Types
//      =======================================================================
        enum MenuChoices  {Quit, Insert, Train, Test, SetLogic, Print, Delete};
        enum LogicChoices {True, False, AND, NAND, OR, NOR, XOR, XNOR, 
                           A, B, NotA, NotB, AandNotB, NotAandB, AorNotB, NotAorB, LearnAll};
//      ======================================================================================

        public:

//      =======================
//      public member functions
//      =======================

//          ===================
//          Default constructor
//          ===================
            Menu(void) {
                userMenuSelection = Quit;
                userLogicSelection = False;
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

//          ===========
//          MenuDisplay
//          ====================
            void MenuDisplay() {
                cout << "+-----------------------------+" << endl;
                cout << "|           Options           |" << endl;
                cout << "+-----------------------------+" << endl;
                cout << "| 1:  Quit       2:  Insert   |" << endl;
                cout << "| 3:  Train      4:  Test     |" << endl;
                cout << "| 5:  Set Logic  6:  Print    |" << endl;
                cout << "| 7:  Delete                  |" << endl;
                cout << "+-----------------------------+" << endl;
            } // Display
//          ============

//          ============
//          LogicDisplay
//          =====================
            void LogicDisplay() {
                cout << "+-----------------------------+" << endl;
                cout << "|        Logic Options        |" << endl;
                cout << "+-----------------------------+" << endl;
                cout << "|  1: True        2: False    |" << endl;
                cout << "|  3: AND         4: NAND     |" << endl;
                cout << "|  5: OR          6: NOR      |" << endl;
                cout << "|  7: XOR         8: XNOR     |" << endl;
                cout << "|  9: A          10: B        |" << endl;
                cout << "| 11: A'         12: B'       |" << endl;
                cout << "| 13: A ∧ B'     14: A' ∧ B   |" << endl;
                cout << "| 15: A ∨ B'     16: A' ∨ B   |" << endl;
                cout << "| 17: Learn All               |" << endl;
                cout << "+-----------------------------+" << endl;
            } // LogicDisplay
//          =================

//          =================
//          printCurrentLogic
//          ==================================
            void printCurrentLogic(ANN &ann) {

                vector<float> truthTable = ann.returnTruthTable();
                
                cout << "+-----------------------------+" << endl;
                cout << "|     Logic Operator: ";          
                switch (userLogicSelection) {
                    case True: 
                        cout << "True    |" << endl;
                        break;
                    case False:
                        cout << "False   |" << endl;
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
                    case A:
                        cout << "A       |" << endl;
                        break;
                    case B:
                        cout << "B       |" << endl;
                        break;
                    case NotA:
                        cout << "A'      |" << endl;
                        break;
                    case NotB:
                        cout << "B'      |" << endl;
                        break;
                    case AandNotB:
                        cout << "A ∧ B'  |" << endl;
                        break;
                    case NotAandB:
                        cout << "A' ∧ B  |" << endl;
                        break;
                    case AorNotB:
                        cout << "A ∨ B'  |" << endl;
                        break;
                    case NotAorB:
                        cout << "A' ∨ B  |" << endl;
                        break;
                    case LearnAll:
                        cout << "All     |" << endl;
                        break;
                    default:
                        cout << "UNKNOWN |" << endl;
                        break;
                }
                if (userLogicSelection != LearnAll) {
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
                }
            } // printCurrentLogic()
//          ========================

//          =========
//          QueryUser
//          ==========================
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
                    case 6: userMenuSelection = Print;
                        break;
                    case 7: userMenuSelection = Delete;
                        break;
                    default: userMenuSelection = Quit;
                        break;
                }
                cout << endl;
            } // QueryUser
//          ==============

//          ==============
//          QueryUserLogic
//          =======================
            void QueryUserLogic() {
                LogicDisplay();

                int selection;
                cout << "Enter selection for logic gate: ";
                cin >> selection;
                cout << endl;

                switch (selection) {
                    case 1: userLogicSelection = True;
                        break;
                    case 2: userLogicSelection = False;
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
                    case 9: userLogicSelection = A;
                        break;
                    case 10: userLogicSelection = B;
                        break;
                    case 11: userLogicSelection = NotA;
                        break;
                    case 12: userLogicSelection = NotB;
                        break;
                    case 13: userLogicSelection = AandNotB;
                        break;
                    case 14: userLogicSelection = NotAandB;
                        break;
                    case 15: userLogicSelection = AorNotB;
                        break;
                    case 16: userLogicSelection = NotAorB;
                        break;
                    case 17: userLogicSelection = LearnAll;
                        break;
                    default: userLogicSelection = LearnAll;
                        break;
                }; // switch
            } // QueryUserLogic()
//          =====================

//          ==============
//          processCommand
//          ===============================
            void processCommand(ANN &ann) {

                int layer;
                bool iterate;

                if (userMenuSelection != Quit) {
                    switch (userMenuSelection) {
                        case Insert:
                            int layer;
                            do {
                                iterate = false;
                                cout << "Choose Layer to insert node: ";
                                cin >> layer;
                                if (cin.fail()) {
                                    iterate = true;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Error: Invalid input." << endl;
                                }
                            } while (iterate);
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
                        case Print:
                            ann.printANN();
                            break;
                        case Delete:
                            cout << "Choose layer to delete from: ";
                            cin >> layer;
                            ann.deleteNode(layer);
                            break;
                        default:
                            cout << "Invalid selection" << endl;
                            break;
                    }
                }
            } // processCommand
//          ===================

//          ===================
//          ProcessLogicCommand
//          ====================================
            void ProcessLogicCommand(ANN &ann) {
                vector<float> truthTable;
                ann.setAllGates(false);
                switch (userLogicSelection) {
                    case True: 
                        truthTable = {1, 1, 1, 1};
                        ann.setTruthTable(truthTable);
                        break;
                    case False:
                        truthTable = {0, 0, 0, 0};
                        ann.setTruthTable(truthTable);
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
                    case A:
                        truthTable = {0, 0, 1, 1};
                        ann.setTruthTable(truthTable);
                        break;
                    case B:
                        truthTable = {0, 1, 0, 1};
                        ann.setTruthTable(truthTable);
                        break;
                    case NotA:
                        truthTable = {1, 1, 0, 0};
                        ann.setTruthTable(truthTable);
                        break;
                    case NotB:
                        truthTable = {1, 0, 1, 0};
                        ann.setTruthTable(truthTable);
                        break;
                    case AandNotB:
                        truthTable = {0, 0, 1, 0};
                        ann.setTruthTable(truthTable);
                        break;
                    case NotAandB:
                        truthTable = {0, 1, 0, 0};
                        ann.setTruthTable(truthTable);
                        break;
                    case AorNotB:
                        truthTable = {1, 1, 0, 1};
                        ann.setTruthTable(truthTable);
                        break;
                    case NotAorB:
                        truthTable = {1, 0, 1, 1};
                        ann.setTruthTable(truthTable);
                        break;
                    case LearnAll:
                        ann.setAllGates(true);
                        break;
                    default:
                        break;
                }
            } // ProcessLogicCommand
//          ========================

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

    }; // Menu
//  ==========
