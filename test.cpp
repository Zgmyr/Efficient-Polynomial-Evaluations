// messing around with <gmpxx.h>

#include <iostream>
#include <limits>
#include <fstream>
#include <random>
using namespace std;

int main() {

    // cerr << "ERROR MESSAGE HERE" << endl;
    // exit(1);
    // cout << "Will i execute?" << endl;

    /* RAND TEST */
    random_device myEngine;
    uniform_int_distribution<int> randInt(0,100);

    int x = randInt(myEngine);
    cout << "(1) RANDOM INT = " << x << endl;

    x = randInt(myEngine);
    cout << "(2) AGAIN = " << x << endl;
    
    cout << "THREE MORE TIMES:" << endl;
    for (int i = 0; i < 3; i++)
    {
        x = randInt(myEngine);
        cout << x << endl;
    }

    /* FILE OUTPUT TEST */
    // ofstream oFile("testdoc.txt", ios::app);
    
    // if (oFile.is_open()) {
    //     cout << "Opened file" << endl;

    //     oFile << "Hello World!" << endl;

    //     oFile << "New LINE!" << endl;
    // }
    // else {
    //     cout << "FILE NOT OPENED" << endl;
    // }

    // oFile.close();


    /* FILE INPUT/READ TEST */
    // ifstream iFile("testdoc.txt");

    // string input;
    // if (iFile) {
    //     cout << "File opened" << endl;
        
    //     while (iFile >> input)
    //     {
    //         cout << input << endl;
    //     }

    //     iFile.close();
    // }
    
    return 0;
}