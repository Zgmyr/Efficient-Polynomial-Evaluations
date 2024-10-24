// messing around with <gmpxx.h>

#include <iostream>
// #include <fstream>
// #include <chrono>
// #include <thread>
// #include <math.h>
#include <gmpxx.h>
#include <vector>
using namespace std;
// using namespace std::chrono;

int main() {



    // vector<mpz_class> vector1;

    // mpz_class val1 = 123456789;
    // mpz_class val2 = 987654321;

    // vector1.push_back(val1);
    // vector1.push_back(val2);

    // for (const auto& v : vector1) {
    //     cout << v << endl;
    // }

    int arr1[100];
    for (int i=0;i<100;i++) {
        arr1[i] = i;
    }
    for (int& e : arr1) {
        e *= 5;
    }
    for (const int& e : arr1) {
        cout << e << endl;
    }



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