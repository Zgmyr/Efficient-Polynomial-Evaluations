#include <iostream>
#include <fstream>
#include <gmpxx.h>
#include <math.h>
#include <chrono>
#include <limits>
#include <cstdlib>
#include <vector>

#define FILEPATH "coeffAndVars.txt"

// prototype for generating coefficients & variables
void generateCoeffAndVars(int,int);

int main() {

    // controls for first menu
    int choice;
    bool isFinished = false;

    std::cout << "=== Menu ===\n";
    std::cout << "For the general form polynomial P(x) = a_0 + a_1x^1 + a_2x^2 + ... + a_nx^n\n";
    std::cout << "1. Generate new coefficient data\n";
    std::cout << "2. Read existing coefficient data from file\n"
        << "(for the first time running this program, please choose option '1')\n";

    // MENU 1: Generating Coefficient Data or Use Existing
    while (!isFinished) {
        std::cout << "\nEnter your choice (1 or 2): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clear buffer

        switch (choice) {
            case 1:
                std::cout << "Enter a value n for the degree of polynomial P(x): ";

                int degree;
                std::cin >> degree;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clear buffer
                
                std::cout << "Enter a value d for the digit size of coefficients to be generated: ";
                int digits;
                std::cin >> digits;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clear buffer
                
                generateCoeffAndVars(degree,digits);

                isFinished = true;
                break;
            case 2:
                isFinished = true;
                break;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    }

    // open generated (or previously existing) coefficient data for reading
    std::ifstream inFile(FILEPATH);

    // verify file opened properly or report error and end
    if (inFile.is_open()) {
        std::cout << "> Reading coefficients from " << FILEPATH << "\n";
    }
    else {
        std::cout << "\nError in opening file 'coeffAndVars.txt' for reading. Ending program...\n";
        exit(1);
    }

    /* Gathering Polynomial Data from External File (value of x and coefficients) */

    // getting value x from file (first entry)
    int x;
    inFile >> x;
    inFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clear input buffer after reading x
 
    // initialize vector to store large coefficients
    std::vector<mpz_class> coeffVector;
    std::string line;

    // read the file & store each coefficient in coeffVector
    while (getline(inFile, line)) {
        mpz_class num(line); // convert each line into mpz_class (stores large scientific numbers)
        coeffVector.push_back(num); // store in mpz_class vector
    }

    // validation: vector is not empty
    if (coeffVector.size() == 0) {
        std::cout << "\nError: no data was received from 'coeffAndVars.txt'. Run program again and generate new values!\n";
        exit(1);
    }

    // DEBUG: test code to ensure reading data properly
    mpz_class last = coeffVector.back();
    std::cout << "last value = " << last << "\n";
    inFile.close();


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
    while (n < 1 || d < 1)
    {
        std::cout << "\nError: both 'n' and 'd' must be greater than 1. Try again.\n\n";
        
        std::cout << "Enter a new value n (greater than 1) for the degree of polynomial P(x): ";
        std::cin >> n;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clear buffer

        std::cout << "Enter a new value d (greater than 1) for the digit size of coefficients to be generated: ";
        std::cin >> d;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clear buffer
    }

    // initialize output file
    std::ofstream outFile(FILEPATH);

    // ensure file opened properly
    if (outFile.is_open()) {
        std::cout << "> Generating " << n+1 << " new " << d << "-digit coefficient values in "
            << "'coeffAndVars.txt' ...\n";
    }
    else {
        std::cout << "Error in opening file 'coeffAndVars.txt' for writing. Ending program...\n";
        exit(1);
    }

    // generate random value for 'x' & write to file
    std::srand(time(0)); // random seed
    int x = rand() % 100 + 1; // range is from 1 to 100, for simplicity
    outFile << x << "\n";

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

        outFile << random_num << "\n";

        mpz_clear(random_num); // cleanup
    }

    // cleanup GMP & close file
    gmp_randclear(rand_state);
    outFile.close();

    // report successful operation
    std::cout << "> 'coeffAndVars.txt' has successfully been updated with new coefficient values!\n";

    // DEBUG - use this to see evaluation time of coefficient generation
    /* duration<double> eval_time = steady_clock::now() - start_time;

    double eval_s = eval_time.count();
    double eval_ms = eval_s * 1000;

    cout << "Process time (ms): " << eval_ms << endl; */
}