/*
 * Miller Rabin
 *
 * What this file does:
 * Tests whether a large integer is prime using repeated modular exponentiation and witnesses.
 *
 * Typical problem to recognize:
 * A witness is a base that proves a number is composite.
 *
 * Complexity / constraints:
 * The deterministic 64-bit witness set in the source should be kept unchanged.
 *
 * Main variables:
 * n = number being tested; d = odd part of n-1; s = number of factors of 2; a = witness.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * a: main input/base/coefficient.
 * d: divisor / gcd result / distance depending on function.
 * x: unknown or current value.
 * r: chosen count / remainder / right bound.
 * i: loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

//remember use safe mul at the fastpower function

// Function: check_composite(int n, int a, int d, int s).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool check_composite(int n, int a, int d, int s) {
    int x = fast_power(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (int)SafeMul(x,x,n);
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(int n, int iter=100) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    int d = n - 1;
    while ((d & 1ll) == 0) {
        d >>= 1ll;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}
