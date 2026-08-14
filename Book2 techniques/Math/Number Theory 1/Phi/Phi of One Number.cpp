/*
 * Phi of One Number
 *
 * What this file does:
 * Computes Euler’s totient φ(n), the number of integers in [1,n] coprime to n.
 *
 * Typical problem to recognize:
 * Coprime means gcd(a,n)=1. Euler phi is multiplicative for coprime arguments.
 *
 * Complexity / constraints:
 * Sieve versions compute φ for all numbers; single-number versions factor n.
 *
 * Main variables:
 * n = input; phi[i] = totient table; p = prime factor.
 *
 * Variable guide for names used in this implementation:
 * phi: Euler totient values/result.
 * n: main size/index/input value.
 * i: loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: phi(int n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}
