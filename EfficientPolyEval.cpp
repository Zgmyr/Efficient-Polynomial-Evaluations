#include <iostream>
#include <fstream>
#include <random>
#include <math.h>
using namespace std;

// prototype for generating coefficients & variables
void generateCoeffAndVars(int,long int);

int main() {

    /* 
    DRIVER:
    MENU:
        1. GENERATE NEW DATA
        2. USE EXISTING DATA
    (1) DO:
        ASK FOR N and D
        PASS N and D TO GENERATE COEFF&VAR TO UPDATE DATA
    (2) SKIP...

    INITIALIZE VECTOR TO HOLD COEFFICIENTS & X

    MENU:
        1. BRUTE
        2. REPEATED
        3. HORNERS
    
    (1 | 2 | 3) DO:
        PASS IN VECTOR OF COEFF TO ALGORITHM 
        START TIMER
        EVALUATES
        END TIMER
    */

   generateCoeffAndVars(15,10);

   return 0;
}

// function generates and writes to file (in order) (1) a value 'x' (range 1-100), and (2) 'n+1' list
//      of 'd' digit sized coefficent values. This data is to be used by the three polynomial evaluation algorithms.
/* ISSUES:
    - can't go larger than 10 digits (overflow error of max int value)
    - not uniformly 10 digit numbers (is this acceptable? Probably)*/
void generateCoeffAndVars(int n, long int d) {

    // Validation: ensure n and d are at least 1
    if (n < 1 || d < 1)
    {
        cerr << "Both n and d must be at least 1." << endl;
        return;
    }

    // initialize output file
    ofstream inFile("coeffAndVars.txt");

    // ensure file opened properly
    if (!inFile.is_open()) {
        cout << "Error in opening file 'coeffAndVars.txt' for writing. Ending program..." << endl;
        exit(1);
    }

    // seed randomizer for generating coefficients
    srand(time(0));
    random_device myEngine;
    uniform_int_distribution<long int> randInt(1,2147483647);

    // generate random value for 'x' (for simplicity, between 1-100)
    int x = rand() % 100 + 1;
    inFile << x << endl; // write 'x' to file as first value

    // generate 'n+1' coefficients for the polynomial, each with 'd' digits
    for (int i = 0; i <= n; i++)
    {
        // generate random 'd'-digit coefficient
        int coefficient = randInt(myEngine) % static_cast<int>(pow(10,d));

        inFile << coefficient << endl;
    }

    cout << "DEBUG: Subprogram ran successfully" << endl;

    inFile.close();
}