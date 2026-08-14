/*
 * Fast Power
 *
 * What this file does:
 * Computes a^b in O(log b) using binary exponentiation. Use it whenever the exponent is too large for a linear loop, especially for modular powers, inverses, matrix/permutation jumping, and geometric expressions.
 *
 * Typical problem to recognize:
 * Binary exponentiation means repeatedly squaring the base and using the set bits of the exponent.
 *
 * Complexity / constraints:
 * Input constraints usually allow b up to 1e18.
 *
 * Main variables:
 * a = base; b = exponent; mod = modulus when present; res/ans = accumulated answer.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * m: second size or modulus.
 * res: accumulated result.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: binpow(long long a, long long b, long long m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
