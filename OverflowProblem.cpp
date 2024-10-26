// Zachary Gmyr
// 3130-001
// Project 1: Evaluating Polynomials

/* Description: in this program we attempt to calculate the result of a large polynomial, P(x,n) = 1 + x + 2x^2 + 3x^2 + ... + nx^n,
    purposely causing overflow error to occur & demonstrating the long type's capacity.
    
    We should observe that when large values for x and n are used, the returned result is a negative value. This suggests that
    the arithmetic operations between the expressions caused the returned long to exceed its maximum value. */

#include <iostream>
using namespace std;

// function prototype for testPolynomial
long testPolynomial(int,int);

int main() {

    cout << "Evaluating P(x,n) = 1 + x + 2x^2 + 3x^2 + ... + nx^n" 
        << "\nObserve overflow for P(123,25):" << endl;

    /* P(x,n) = 1 + x + 2x^2 + 3x^3 + ... + nx^n */

    // Evaluate polynomial for x=1, n=1
    long var1 = testPolynomial(1,1);
    cout << "P(1,1) = " << var1 << endl;

    // Evaluate polynomial for x=3, n=2
    long var2 = testPolynomial(3,2);
    cout << "P(3,2) = " << var2 << endl;

    // Evaluate polynomial for x=5, n=4
    long var3 = testPolynomial(5,4);
    cout << "P(5,4) = " << var3 << endl;

    // Evaluate polynomial for x=123, n=25
    long var4 = testPolynomial(123,25);
    cout << "P(123,25) = " << var4 << endl;

    // did we appear to have overflow on this last one?
    if (var4 < 0)
        cout << "Oh no! It seems overflow occurred." << endl;

    return 0;
}

// Function to evaluate the polynomial P(x,n) = 1 + x + 2x^2 + 3x^2 + ... + nx^n
long testPolynomial(int x, int n) {
    // initialize the result to store the sum of the polynomial terms
    long result = 0;

    // Loop from 0 to n to calculate each term of the polynomial
    for (int i = 0; i <= n; i++) {
        // initialize variable to calculate x^i, starting at 1 (x^0)
        long varExpr = 1;

        // calculating x^i (varExpr) by multiplying x for i times
        for (int j = 0; j < i; j++) {
            varExpr *= x;
        }

        // add the current term (coefficient * variable expression) to the result
        result += i * varExpr; // result = result + term (i * x^i)
    }

    // increment result by 1 (for the constant term)
    return ++result;
}



