    #include <iostream>
    #include "ANN.hpp"
    #include "Menu.hpp"

    using namespace std;

    void imageProcessor(const string&);

    int main() {

        ANN ann;
        Menu menu;
        
        ann.insert(1, 0);
        ann.insert(1, 0);

        ann.insert(2, 0);
        ann.insert(2, 0);
        ann.insert(2, 0);

        ann.insert(3, 0);
        ann.insert(3, 0);
        ann.insert(3, 0);

        ann.insert(4, 0);
        ann.insert(4, 0);
        
        do {
            menu.QueryUser(ann);
            menu.processCommand(ann);
        } while (menu.Continue());
        

        cout << endl;
    }
