// messing around with <gmpxx.h>

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <thread>
#include <math.h>
#include <gmpxx.h>
using namespace std;
using namespace std::chrono;

int main() {

    /* Chrono Test */

    // beginning reference point
    // time_point<steady_clock> start = steady_clock::now();

    // this_thread::sleep_for(5s);

    // // ending reference point
    // time_point<steady_clock> end = steady_clock::now();

    // // NOTE: duration<double> defaults to (s)
    // // duration<double> elapsed_time = end - start;
    // // OR
    // duration<double> elapsed_time = steady_clock::now() - start;

    // cout << "Elapsed time (ms): " << duration_cast<milliseconds>(elapsed_time).count() << endl;





    mpz_t random_num;
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
    cout << random_num << endl;

    /*
    PSEUDOCODE FOR GENERATING RANDOM 'd'-DIGIT #'s:
    
    given values 'n' and 'd'
    initialize vars (random state, any mpz_t values, etc.)
        -> double log2_10 = log(10.0) / log(2.0);
    take 'd' and convert to bits such that:
        -> double bitcount = d * log2(10)
    loop for n+1 times to generate:


    */
    








    /* RAND TEST*/

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
    




    /* RAND TEST */
    // random_device myEngine;
    // uniform_int_distribution<int> randInt(0,100);

    // int x = randInt(myEngine);
    // cout << "(1) RANDOM INT = " << x << endl;

    // x = randInt(myEngine);
    // cout << "(2) AGAIN = " << x << endl;
    
    // cout << "THREE MORE TIMES:" << endl;
    // for (int i = 0; i < 3; i++)
    // {
    //     x = randInt(myEngine);
    //     cout << x << endl;
    // }




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