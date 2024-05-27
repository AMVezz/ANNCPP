    #include <iostream>
    #include "ANN.hpp"
    #include "Menu.hpp"

    using namespace std;

    int main() {

        ANN ann;
        Menu menu;
        
        ann.insert(1, 0);
        ann.insert(1, 0);

        for (int i = 0; i < 4; i++) {
            ann.insert(1, 0.5);
        }
        for (int i = 0; i < 8; i++) {
            ann.insert(2, 0.5);
        }
        for (int i = 0; i < 8; i++) {
            ann.insert(3, 0.5);
        }
        for (int i = 0; i < 8; i++) {
            ann.insert(4, 0.5);
        }

        ann.insert(5, 0);
        ann.insert(5, 0);
        
        do {
            menu.QueryUser(ann);
            menu.processCommand(ann);
        } while (menu.Continue());
        

        cout << endl;
    }
