// messing around with <gmpxx.h>

#include <iostream>
// #include <fstream>
// #include <chrono>
// #include <thread>
// #include <math.h>
#include <gmpxx.h>
#include <vector>
#include <deque>
using namespace std;
// using namespace std::chrono;

int main() {

    int x = 4;
    int degree = 2;
    mpz_class var_expr = 1;
    for (int n = 0; n < degree; n++) {
            var_expr *= x;
    }
    std::cout << "var_expr = " << var_expr << "\n";






    /* DEQUE TESTING 
    (remembering how to work with DEQUE's)*/
    /* std::deque<int> myDEQUE = {1,2,3,4};
    std::cout << "First element = " << myDEQUE.front() << "\n";
    std::cout << "Size = " << myDEQUE.size() << "\n";

    int first = myDEQUE.front();
    myDEQUE.pop_front();

    std::cout << "First element (popped) = " << first << "\n";
    std::cout << "New first element = " << myDEQUE.front() << "\n";
    std::cout << "Size = " << myDEQUE.size() << "\n";

    for (auto& e : myDEQUE) {
        std::cout << e << " ";
    }
    std::cout << "\nEND\n"; */



    /* Vector<mpz_class> Testing */
    // unit test, messing with mpz_class
    /* std::cout << "Last element: " << coeffVector.back() << "\n";
    mpz_class a = coeffVector.back();
    coeffVector.pop_back();

    std::cout << "Last element: " << coeffVector.back() << "\n";
    mpz_class b = coeffVector.back();
    coeffVector.pop_back();
    std::cout << "Last element: " << coeffVector.back() << "\n";

    mpz_class sum = a + b;
    std::cout << "sum = " << sum << "\n"; */







    /* Chrono Test */
    /* => use this to measure efficiency of algorithms (duration) */

    /* beginning reference point
    time_point<steady_clock> start = steady_clock::now();

    this_thread::sleep_for(5s);

    // ending reference point
    time_point<steady_clock> end = steady_clock::now();

    // NOTE: duration<double> defaults to (s)
    // duration<double> elapsed_time = end - start;
    // OR
    duration<double> elapsed_time = steady_clock::now() - start;

    cout << "Elapsed time (ms): " << duration_cast<milliseconds>(elapsed_time).count() << endl; */






    /* VERY LARGE RAND # GENERATION */

    /* mpz_t random_num;
    gmp_randstate_t rand_state;
    
    // Initialize random state
    gmp_randinit_mt(rand_state);  // Mersenne Twister algorithm for random state
    gmp_randseed_ui(rand_state, time(0));  // Seed with the current time

    mpz_init(random_num);

    // mpz_rrandomb (mpz_t rop, gmp_randstate_t state, mp_bitcnt_t n)
    // Bits = #digits * log_2(10)

    int d = 10;
    double log2_10 = log(10.0) / log(2.0);
    double bit_count = d * log2_10;
    mpz_rrandomb(random_num, rand_state, bit_count);
    cout << random_num << endl; */


    


    /* RAND TEST*/
    /* => SIMPLE. use for generating x */

    // cout << time(0) << endl;

    // // seed random generator
    // srand(time(0));
    
    // // generate #s
    // for (int i = 0; i < 5; i++)
    // {
    //     int randomNum = rand(); // generate #

    //     // restrict to 1-100
    //     int rNum = randomNum % 100 + 1;

    //     cout << rNum << endl;
    // }
    




    /* FILE OUTPUT TEST */
    /* testing file stream operations */
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