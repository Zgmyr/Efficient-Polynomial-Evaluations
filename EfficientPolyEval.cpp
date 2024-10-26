// Zachary Gmyr
// 3130-001
// October 25, 2024
// Project 1: Evaluating Polynomials

/* Description: This program uses three different algorithms to evaluate the polynomial P(x) = a_0 + a_1x^1 + a_2x^2 + ... + a_nx^n.
    (1) Brute Force       -> O(n^2)
    (2) Repeated Squares  -> O(nlogn)
    (3) Horner's Rule     -> O(n)

    We use an external file 'coeffAndVars.txt' in order to generate and store data for our polynomial such as the value for x, the size
    'n' of our polynomial, size 'd'-digits of our coefficients, and the coefficients themselves. This file is read by our driver and fed
    into one of the three algorithms for evaluation. In order to compute extremely large polynomials and avoid overflow error in the
    cases where large values are entered for 'n' and 'd', we use GNU Multiple Precision library (<gmpxx.h>). In order to measure evaluation
    time of each of our algorithms we use the chrono library (<chrono>) and mark a time_point at the beginning and end of each function.
    Evaluation time is determined by subtracting the start point from the end point. For further information about this project, refer
    to the README.md file.
    */

#include <iostream>
#include <fstream>
#include <gmpxx.h>
#include <math.h>
#include <chrono>
#include <limits>
#include <cstdlib>
#include <deque>
#include <algorithm>

#define FILEPATH "coeffAndVars.txt" // external file, will write x, n, d and coefficient values to

/* Function Prototypes */

void generateCoeffAndVars(int,int);

mpz_class bruteForceAlgorithm(std::chrono::duration<double>&, int, std::deque<mpz_class>);

mpz_class repeatedSquaringAlgorithm(std::chrono::duration<double>&, int, const std::deque<mpz_class>);

mpz_class hornersRuleAlgorithm(std::chrono::duration<double>&, int, const std::deque<mpz_class>);

int main() {

    // controls for first menu
    int choice;
    bool isFinished = false;

    // prompt for first menu
    std::cout << "=== Coefficient Data ===\n";
    std::cout << "For the general form polynomial P(x) = a_0 + a_1x^1 + a_2x^2 + ... + a_nx^n\n";
    std::cout << "1. Generate new coefficient data\n";
    std::cout << "2. Read existing coefficient data from file\n"
        << "(for the first time running this program, please choose option '1')\n";

    /* MENU 1: Generating Coefficient Data or Use Existing */
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
                std::cout << "Invalid choice. Please enter a number 1 or 2.\n";
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

    /* Gathering Polynomial Data from External File (value of x and coefficients).
        The values to be passed into our polynomial algorithms:
        1. value of x
        2. coefficients (deque)
        3. chrono duration to measure evaluation time */

    // getting values x, n, and d from file (first line)
    int x, n, d;
    inFile >> x;
    inFile >> n;
    inFile >> d;

    inFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clear input buffer after reading first line
 
    // initialize deque to store large coefficients
    std::deque<mpz_class> coeffDeque;
    std::string line;

    // initialize time variable to keep track of evaluation time (NOTE: this should be passed to our polynomial functions by reference)
    std::chrono::duration<double> elapsed_time;

    // initialize an mpz_class to store result of our polynomial evaluation (this may be a LARGE nubmer!!!!)
    mpz_class result;

    // read the file & store each coefficient in coeffDeque
    while (getline(inFile, line)) {
        mpz_class num(line); // convert each line into mpz_class (stores large scientific numbers)
        coeffDeque.push_back(num); // store in mpz_class deque
    }

    // validation: deque is not empty
    if (coeffDeque.size() == 0) {
        std::cout << "\nError: no data was received from 'coeffAndVars.txt'. Run program again and generate new values!\n";
        exit(1);
    }

    // close coefficient data file
    inFile.close();

    // reset controls for second menu
    isFinished = false;

    // prompt for second menu
    std::cout << "\n=== Evaluation Algorithm ===\n";
    std::cout << "For the general form polynomial P(x) = a_0 + a_1x^1 + a_2x^2 + ... + a_nx^n\n";
    std::cout << "1. Run Brute Force Algorithm\n";
    std::cout << "2. Run Repeated Squares Algorithm\n";
    std::cout << "3. Run Horner's Rule Algorithm\n";

    /* MENU 2: Which algorithm to run? */
    while (!isFinished) {
        std::cout << "\nEnter your choice (1 | 2 | 3): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // clear buffer

        switch (choice) {
            case 1:
                std::cout << "Evaluating P(x) using brute force: x = " << x << ", n = " << n << ", d = " << d << "\n";
                result = bruteForceAlgorithm(elapsed_time,x,coeffDeque);
                isFinished = true;
                break;
            case 2:
                std::cout << "Evaluating P(x) using repeated squares: x = " << x << ", n = " << n << ", d = " << d << "\n";
                result = repeatedSquaringAlgorithm(elapsed_time,x,coeffDeque);
                isFinished = true;
                break;
            case 3:
                std::cout << "Evaluating P(x) using horner's rule: x = " << x << ", n = " << n << ", d = " << d << "\n";
                // IMPORTANT: hornersRuleAlgorithm() depends on a reversed array of coefficients because we evaluate backward (nested)
                std::reverse(coeffDeque.begin(),coeffDeque.end());
                result = hornersRuleAlgorithm(elapsed_time,x,coeffDeque);
                isFinished = true;
            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        }
    }

    std::cout << "result = " << result << "\n";
    std::cout << "elapsed time (ms) = " << elapsed_time.count() * 1000 << "\n";

   return 0;
}

/* GENERATECOEFFANDVARS - this function uses GNU multi-precision to generate and write to an external file:
    line 1:
        (1)  a value 'x' (within the range 1 ... 100 for simplicty)
        (2) value 'n' of the degree polynomial being stored in file
        (3) value 'd' of the d-digits coefficient values generated to the file
    lines 2 (onward):
        (4) 'n+1' list of 'd'-digit coefficient values (includes the constant term)
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
    outFile << x << " ";

    // write in values of n & d
    outFile << n << " ";
    outFile << d << "\n";

    /* Initialize random state for large random number generation */
    gmp_randstate_t rand_state;
    gmp_randinit_mt(rand_state);  // Mersenne Twister algorithm for random state
    gmp_randseed_ui(rand_state, time(0));  // Seed with the current time

    // determine bit count for 'd'-digits (bit count needed by mpz_rrandomb to generate bit count-sized digits)
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

/* BRUTE FORCE ALGORITHM - this function calculates each multiplication of x by hand (i.e. x is multiplied explicitly
    n-number of times at each degree 'n' of our polynomial). This function uses GNU multiple precision library to handle
    the large values calculated for each term. Chrono is used to return the evaluation time from beginning of function
    to the end of the function. */
mpz_class bruteForceAlgorithm(std::chrono::duration<double>& t, int x, std::deque<mpz_class> coefficients) {
    using namespace std::chrono;
    // EVALUATING: P(x) = a_0 + a_1x^1 + a_2x^2 + ... + a_nx^n => BRUTE FORCE
    
    // mark the start time of evaluating this algorithm
    time_point<steady_clock> start_time = steady_clock::now();

    // accumulator to be returned (initialize with constant term)
    mpz_class result = coefficients.front();
    coefficients.pop_front(); // pop constant term (a_0)

    // counter to keep track of current term
    int degree = 1;

    // loop through each term (following the constant) & calculate each term of polynomial by hand
    for (auto& coeff : coefficients) {
        // initialize temp variables to store variable expression (x^n)
        mpz_class var_expr = 1;

        // calculate each and every multiplication of the x term with brute force
        for (int n = 0; n < degree; n++) {
            var_expr *= x; // multiplying x for 'n' times
        }

        // increment to next term
        degree++;

        // add current term to result
        result += coeff * var_expr;
    }

    // mark the end time of evaluating this algorithm, & update the evaluation time in driver
    time_point<steady_clock> end_time = steady_clock::now();
    t = end_time - start_time;

    return result;
}

/* POWER - this is a helper function to be used by the repeated squaring algorithm. Using this function, we
    are able to efficiently calculate the power of a given base using GNU multiple precision library to avoid
    overflow error (as opposed to simply using pow() from <math.h>, which would cause overflow working with
    extremely large values).
    
    EXAMPLE: when calling power(2,9), we calculate x^9 by first calculating x * x^8, and x^8 is determined by
    x^4 * x^4, where x^4 is calculated from x^2 * x^2, and x^2 is of course x * x. x is calculated first, then
    base is incremented to x^8 through squaring. This value for x^8, after calculated, is mutliplied by x */
mpz_class power(mpz_class base, int exponent) {
    mpz_class result = 1; // accumulator result
    
    while (exponent > 0) {
        // if exponent is odd
        if (exponent % 2 == 1) {
            result *= base; // multiply base into the result
        }

        // square the base (x = x^2) - repeated squaring
        base *= base;
        // divide exponnet (int) by 2
        exponent /= 2;
    }
    return result; // this might be huge number (mpz_class)
}

/* REPEATED SQUARING ALGOIRHTM - this function calculates each multiplication of x using repeated squaring technique via
    our helper function power(). This function uses GNU multiple precision library to handle the large values calculated
    for each term. Chrono is used to return the evaluation time from beginning of function to the end of the function. */
mpz_class repeatedSquaringAlgorithm(std::chrono::duration<double>& t, int x, const std::deque<mpz_class> coefficients) {
    using namespace std::chrono;
    // EVALUATING: P(x) = a_0 + a_1x^1 + a_2x^2 + ... + a_nx^n => REPEATED SQUARING

    // mark the start time of evaluating this algorithm
    time_point<steady_clock> start_time = steady_clock::now();

    // accumulator to be returned (initialize with constant term)
    mpz_class result = coefficients.front();

    // loop through each coefficient starting from the first power (n = 1)
    for (size_t degree = 1; degree < coefficients.size(); degree++) {
        const auto& coeff = coefficients[degree]; // access each coefficient in order starting with the second
        mpz_class var_expr = power(x, degree); // calculate x^degree using repeated squaring

        // add current term to result
        result += coeff * var_expr;
    }

    // mark the end time of evaluating this algorithm, & update the evaluation time in driver
    time_point<steady_clock> end_time = steady_clock::now();
    t = end_time - start_time;

    return result;
}

/* HORNERS RULE ALGORITHM - this function applies horner's rule to evaluate a polynomial by nesting the evaluation of
    x times (*) the previous result added (+) to the next term. This function uses GNU multiple precision library to
    handle the large values calculated for each term. Chrono is used to return the evaluation time from beginning of
    function to the end of the function.A properly nested polynomial (using Horner's Rule) appears in the following form:

    P(x) = a_0 + a_1x^1 + a_2x^2 + a_3x^3
    P(x) = a_0 + x(a_1 + x(a_2 + a_3x)) ... x is multiplied in to a_3 three times (x^3)

    NOTE: due to the nested evaluation of this function, coefficients deque should be passed in backwards!!!*/
mpz_class hornersRuleAlgorithm(std::chrono::duration<double>& t, int x, const std::deque<mpz_class> coefficients) {
    using namespace std::chrono;
    // EVALUATING: P(x) = a_0 + a_1x^1 + a_2x^2 + ... + a_nx^n => HORNER'S RULE

    // mark the start time of evaluating this algorithm
    time_point<steady_clock> start_time = steady_clock::now();

    // initialize accumulator
    mpz_class result = 0;

    // evaluating using Horner Rule
    for (const auto& coeff : coefficients) {
        result = result * x + coeff; // nested evaluation
    }

    // mark the end time of evaluating this algorithm, & update the evaluation time in driver
    time_point<steady_clock> end_time = steady_clock::now();
    t = end_time - start_time;

    return result;
}