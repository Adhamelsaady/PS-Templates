/*
 * Prime Factorization
 *
 * What this file does:
 * Factorizes integers into primes, using trial division for small values or Pollard Rho for 64-bit values.
 *
 * Typical problem to recognize:
 * Prime factorization writes n as a product of prime powers.
 *
 * Complexity / constraints:
 * Use Miller-Rabin + Pollard Rho for n up to 64-bit.
 *
 * Main variables:
 * n = number to factor; p = prime factor; cnt/exponent = its multiplicity; factors = result.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * d: divisor / gcd result / distance depending on function.
 * i: loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: trial_division3(long long n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<long long> trial_division3(long long n) {
    vector<long long> factorization;
    for (int d : {2, 3, 5}) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    int i = 0;
    for (long long d = 7; d * d <= n; d += increments[i++]) {
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
        if (i == 8)
            i = 0;
    }
    if (n > 1)
        factorization.push_back(n);
    return factorization;
}
