/*
 * GCD with Negative Numbers
 *
 * What this file does:
 * Computes the greatest common divisor, including variants for negatives or using only binary operations.
 *
 * Typical problem to recognize:
 * gcd(a,b) is the largest positive integer dividing both numbers.
 *
 * Complexity / constraints:
 * Binary GCD uses shifts/subtraction; Extended Euclid also gives coefficients.
 *
 * Main variables:
 * a,b = input integers; x,y = Bézout coefficients in extended Euclid; g = gcd.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * q: quotient or second input.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: gcd(int a, int b, int& x, int& y).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
