    #include <iostream>
    #include "ANN.hpp"

    using namespace std;

    void imageProcessor(const string&);

    int main() {

        ANN ann;
        
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


        int iterations;
        cout << "iterations: ";
        cin >> iterations;  
        
        for (int i = 0; i < iterations; i++) {
            ann.ForwardPropogation("backPass");
        }

        cout << endl;
    }
