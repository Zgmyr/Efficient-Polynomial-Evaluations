// Zachary Gmyr
// 3130-001
// Project 1: Evaluating Polynomials

/* Description: in this program we use <gmpxx.h> GNU Multi-Precision Library to perform arithmetic operations for
    extremely large/ultra-precise numbers. In our case we are calculating the result of a polynomial where
    overflow error would typically occur using regular int data types.
    
    For quick reference to see how to use <gmpxx.h>:
    variable initialization: https://gmplib.org/manual/Initializing-Integers
    variable assignment: https://gmplib.org/manual/Assigning-Integers
    integer operations: https://gmplib.org/manual/Integer-Arithmetic
    
    As a result of using mpz_t types for polynomial evaluation, we can evaluate extremely large polynomials
    and should observe that for the standard polynomial P(x,n) = 1 + x + 2x^2 + 3x^2 + ... + nx^n, that the
    result P(123,25) can be calculated without overflow (i.e. a positive integer is returned).
    */

#include <iostream>
#include <gmpxx.h>
using namespace std;

// function prototype for testPolynomial
void testPolynomial(mpz_t,int,int);

int main() {

    cout << "Evaluating P(x,n) = 1 + x + 2x^2 + 3x^2 + ... + nx^n" 
        << "\nObserve NO overflow for P(123,25):" << endl;

    // declare & initialize result variable for storing polynomial evaluation
    mpz_t result;
    mpz_init(result);

    /* P(x,n) = 1 + x + 2x^2 + 3x^2 + ... + nx^n */

    // Evaluate polynomial for x=1, n=1
    testPolynomial(result,1,1);
    cout << "P(1,1) = " << result << endl;

    // Evaluate polynomial for x=3, n=2
    testPolynomial(result,3,2);
    cout << "P(3,2) = " << result << endl;

    // Evaluate polynomial for x=5, n=4
    testPolynomial(result,5,4);
    cout << "P(5,4) = " << result << endl;

    // Evaluate polynomial for x=123, n=25
    testPolynomial(result,123,25);
    cout << "P(123,25) = " << result << endl;

    // did we appear to have overflow on this last one?
    if (mpz_sgn(result) < 0)
        cout << "Oh no! It seems overflow occurred." << endl; // we should not see this

    // clear memory allocated for result before exiting
    mpz_clear(result);

    return 0;
}

// Function to evaluate the polynomial P(x,n) = 1 + x + 2x^2 + 3x^2 + ... + nx^n
// NOTE: this function assumes x is an unsigned (positive) integer
void testPolynomial(mpz_t result, int x, int n) {
    
    // initialize result to 0
    mpz_init_set_ui(result,0);

    // initialize variable for x
    mpz_t var;
    mpz_init_set_ui(var,x); // var = x

    // Loop from 0 to n to calculate each term of the polynomial
    for (int i = 0; i <= n; i++) {
        // temporary variable to store the current coefficient (i)
        mpz_t iter;
        mpz_init_set_ui(iter,i); // iter = i

        // variable to hold x^i, initialized to 1
        mpz_t varExpr;
        mpz_init_set_ui(varExpr,1); // varExpr = 1

        // calculating x^i (varExpr) by multiplying x for i times
        for (int j = 0; j < i; j++) {
            mpz_mul(varExpr,varExpr,var); // varExpr = varExpr * var (x)
        }

        // temporary variable to store the current term (i * x^i)
        mpz_t subExpr;
        mpz_init(subExpr);
        mpz_mul(subExpr,iter,varExpr); // calculate the term: i * x^i

        // add current term to the result
        mpz_add(result,result,subExpr); // result = result + subExpr (i * x^i)

        // clear temporary variables to prevent memory leaks
        mpz_clear(iter);
        mpz_clear(varExpr);
        mpz_clear(subExpr);
    }

    // add constant term 1 to the result (P(x) = 1 + ...)
    mpz_t ONE;
    mpz_init_set_ui(ONE,1);
    mpz_add(result,result,ONE); // Add 1 to the result

    // clear the variable holding x to prevent memory leaks
    mpz_clear(var);
    mpz_clear(ONE); // clear the constant term
}



