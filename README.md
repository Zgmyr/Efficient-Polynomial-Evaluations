# Efficient-Polynomial-Evaluation
This project was completed for Design & Analysis of Algorithms (CS3130) with the University of Missouri-St Louis.
#### Introduction
In this project, we compare three different algorithms that are used to evaluate polynomials. The goal is to understand the importance of efficiency of an algorithm. The three algorithms used are (1) Brute Force, (2) Repeated Squares, and (3) Horner's Rule. The polynomials to be evaluated have the following general form:
$$P(x) = a_0+a_1x+a_2x^2+...+a_nx^n$$
When evaluating these three algorithms, we store data for this polynomial in an external file `coeffAndVars.txt`, containing information on a randomly generated value `x`, the degree `n` of the polynomial stored in the file, the value `d` corresponding to the `d`-sized digits used to generate coefficient data, and `n+1` coefficients (including the constant $a_0$).
#### Exploration of Overflow Error and Use of GNU Multiple Precision
In the files `OverflowProblem.cpp` and `UsingGMP.cpp` we explore the overflow error and solution to this problem by using the `<gmpxx.h>` library. Overflow occurs when performing arithmetic operations on values resulting in a value beyond the range of that data type. In C++, a signed 32-bit integer has the range of -2,147,483,648 to 2,147,483,647.

`OverflowProblem.cpp` demonstrates a simple brute force calculation of the Polynomial $P(x)=1+x+2x^2+3x^3+...+nx^n$. We see that for larger inputs of `x` and `n`, overflow occurs returning a negative number. This problem is solved in `UsingGMP.cpp` by using the GNU Multi-Precision library. This library contains data types that allow for arithmetic operations on extremely large numbers, which is necessary for evaluating extremely large polynomials. In the example used, we are able to calculate the above polynomial for when `x` is 123 and `n` is 25.
#### Three Algorithms
In `EfficientPolyEval.cpp` we explore the issue of evaluating the following general-form polynomial using brute force, repeated squares, and Horner's rule:
$$P(x) = a_0+a_1x+a_2x^2+...+a_nx^n$$
(1) Our brute force algorithm in `EfficientPolyEval.cpp` calculates each multiplication of x by hand (i.e. x is multiplied explicitly `n` number of times at each degree `n` of our polynomial).

(2) The repeated squares algorithm calculates each multiplication of x using repeated squaring technique via a helper function `power()`. Using this function, we are able to efficiently calculate the power of a given base using GNU multiple precision library to avoid overflow error (as opposed to simply using `pow()` from `<math.h>`, which would cause overflow working with extremely large values). A given example of using this technique may be seen when calling `power(2,9)`, in which we calculate $x^9$ by first calculating $x * x^8$, and $x^8$ is determined by $x^4 * x^4$, where $x^4$ is calculated from $x^2 * x^2$, and $x^2$ is of course $x * x$.

(3) Horner's rule evaluates the polynomial by nesting the evaluation of $x$ times `*` the previous result added `+` to the next term. In our implementation of Horner's rule, due to the nested evaluation of our function, our list of coefficients is passed in backward.

In evaluating these three algorithms, we use the `<chrono>` library to mark start and end `time_point`'s, and subtract the start from the end time to determine and report evaluation time (ms).
#### Results and Analysis
We can run our program `EfficientPolyEval.cpp` and generate our `x` and coefficient data in order to run test results, determining the evaluation time and concluding which functions are more efficient. We first run the program to test for small values of `n` and `d`, generating a smaller polynomial problem with smaller-digit coefficients. This same polynomial can be reused for the three different algorithms, comparing the resulting evaluation time (ms) of each. Next we increment `n` and `d` to larger numbers and compare the evaluation time (ms) again for the three algorithms.

|                      | Brute Force (ms) | Repeated Squares (ms) | Horners Rule (ms) |
| -------------------- | ---------------- | --------------------- | ----------------- |
| n = 15<br>d = 35     | 0.0171           | 0.0494                | 0.0082            |
| n = 15<br>d = 35     | 0.0209           | 0.0466                | 0.0095            |
| n = 15<br>d = 35     | 0.0208           | 0.058                 | 0.0081            |
| n = 120<br>d = 315   | 0.2637           | 0.1979                | 0.0183            |
| n = 120<br>d = 315   | 0.2586           | 0.2167                | 0.019             |
| n = 120<br>d = 315   | 0.257            | 0.2047                | 0.0168            |
| n = 542<br>d = 678   | 4.669            | 1.7379                | 0.0523            |
| n = 542<br>d = 678   | 4.4943           | 1.6866                | 0.0484            |
| n = 542<br>d = 678   | 4.5661           | 1.6217                | 0.0509            |
| n = 3782<br>d = 4183 | 438.42           | 65.7638               | 1.018             |
| n = 3782<br>d = 4183 | 436.045          | 69.3092               | 0.9051            |
| n = 3782<br>d = 4183 | 429.566          | 59.4561               | 0.9417            |
With smaller values of `n` and `d` we see that brute force performs better than repeated squares, but as `n` and `d` become greater, repeated squares outperforms. in execution time. Horner's rule in all trials performed better than both brute force and repeated squares. We can conclude that Horner's Rule resulted consistently in the fastest execution times regardless of values for `n` and `d`.

This is consistent with our understanding of the time complexity for these three algorithms:
Brute Force: $O(n^2)$
Repeated Squaring: $O(nlogn)$
Horner's Rule: $O(n)$