/*
 * Binary GCD
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
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: gcd(int a, int b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int gcd(int a, int b) {
    if (!a || !b)
        return a | b;
    unsigned shift = __builtin_ctz(a | b);
    a >>= __builtin_ctz(a);
    do {
        b >>= __builtin_ctz(b);
        if (a > b)
            swap(a, b);
        b -= a;
    } while (b);
    return a << shift;
}
