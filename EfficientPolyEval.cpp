#include <iostream>
#include <fstream>
#include <gmpxx.h>
#include <math.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

#define FILEPATH "coeffAndVars.txt"

// prototype for generating coefficients & variables
void generateCoeffAndVars(int,int);

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

    INITIALIZE FILE FOR READING FROM FILEPATH MACRO
    INITIALIZE VECTOR TO HOLD COEFFICIENTS & X
    ITERATE THROUGH UNTIL EMTPY:
        CONVERT THE LINE INTO mpz_class AND STORE IN VECTOR

       *** => make sure to use &reference in range-based for loop later for reading from vector (this might get LARGE for large values n)

    MENU:
        1. BRUTE
        2. REPEATED
        3. HORNERS
    (1 | 2 | 3) DO:
        PASS IN VECTOR OF COEFF TO ALGORITHM 
        START TIMER
        EVALUATES
        END TIMER

       *** => will need to re-do the brute force algorithm for general case polynomial using coefficients read from vector
    
    */

   generateCoeffAndVars(35,25);

   return 0;
}

/* This function uses GNU multi-precision to generate and write to an external file:
    (1) a value 'x' (within the range 1 ... 100 for simplicty)
    (2) 'n+1' list of 'd'-digit coefficient values (includes the constant term)
   This data can then be read to evaluate polynomials P(x) = a_0 + a_1x^1 + a_2x^2 + ... + a_nx^n */
void generateCoeffAndVars(int n, int d) {

    // DEBUG - use this to see evaluation time of coefficient generation (see end of function)
    /* time_point<steady_clock> start_time = steady_clock::now(); */

    // Validation: ensure n and d are at least 1
    if (n < 1 || d < 1)
    {
        cerr << "Both n and d must be at least 1." << endl;
        return;
    }

    // initialize output file
    ofstream inFile(FILEPATH);

    // ensure file opened properly
    if (inFile.is_open()) {
        cout << "> Generating " << n+1 << " new " << d << "-digit coefficient values in "
            << "'coeffAndVars.txt' ..." << endl;
    }
    else {
        cout << "Error in opening file 'coeffAndVars.txt' for writing. Ending program..." << endl;
        exit(1);
    }

    // generate random value for 'x' & write to file
    srand(time(0)); // random seed
    int x = rand() % 100 + 1; // range is from 1 to 100, for simplicity
    inFile << x << endl;

    /* Initialize random state for large random number generation */
    gmp_randstate_t rand_state;
    gmp_randinit_mt(rand_state);  // Mersenne Twister algorithm for random state
    gmp_randseed_ui(rand_state, time(0));  // Seed with the current time

    // determine bit-count for 'd'-digits
    double log2_10 = log(10.0) / log(2.0);
    double bit_count = d * log2_10;

    // generate 'n+1' coefficients for the polynomial, each with 'd' digits
    for (int i = 0; i <= n; i++)
    {
        /* GMP initializations */
        mpz_t random_num; // for holding random coefficient
        mpz_init(random_num);

        // generate random number of 'd'-digits using bitcount of 'd'
        mpz_rrandomb(random_num, rand_state, bit_count);

        inFile << random_num << endl;

        mpz_clear(random_num); // cleanup
    }

    // cleanup GMP & close file
    gmp_randclear(rand_state);
    inFile.close();

    // report successful operation
    cout << "> 'coeffAndVars.txt' has successfully been updated with new coefficient values!" << endl;

    // DEBUG - use this to see evaluation time of coefficient generation
    /* duration<double> eval_time = steady_clock::now() - start_time;

    double eval_s = eval_time.count();
    double eval_ms = eval_s * 1000;

    cout << "Process time (ms): " << eval_ms << endl; */
}