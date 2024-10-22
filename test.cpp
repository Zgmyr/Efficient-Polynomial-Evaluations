// messing around with <gmpxx.h>

#include <iostream>
#include <gmpxx.h>
#include <limits>
using namespace std;

int main() {

    mpz_t x;
    mpz_init_set_ui(x,21474);

    mpz_t y;
    mpz_init_set_si(y,-54);

    // mpz_t result;
    // mpz_init(result);

    // mpz_add(result,x,y);

    // cout << "RESULT = " << result << endl;

    cout << mpz_sgn(x) << endl;
    cout << mpz_sgn(y) << endl;
    
    return 0;
}