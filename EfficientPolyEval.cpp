#include <iostream>
#include <fstream>
#include <random>
using namespace std;

// prototype for generating coefficients & variables
void generateCoeffAndVars(int,int);

int main() {

}

// function generates a value for x & a range 'n+1' coefficients of size 'd' digits
//      then writes them to an external file to be used by the three algorithms
void generateCoeffAndVars(int n, int d) {

    // for generating 

    // file to store the generated variable & coefficients
    ofstream inFile("coeffAndVars.txt");

    // ensure file opened properly
    if (!inFile.is_open()) {
        cout << "Error in opening file 'coeffAndVars.txt' for writing. Ending program..." << endl;
        exit(1);
    }

    // using <random> for generating random integers
    random_device randEngine;
    uniform_int_distribution<int> randInt()

    inFile.close();
}