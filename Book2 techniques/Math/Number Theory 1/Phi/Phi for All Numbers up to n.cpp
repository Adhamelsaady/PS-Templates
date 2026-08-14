/*
 * Phi for All Numbers up to n
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
 * n: main size/index/input value.
 * i: loop index.
 * j: nested loop index.
 * phi: Euler totient values/result.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */


// Function: phi_1_to_n(int n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}    //range [1,n]

//a^n congerns a^(a%phi(m))  under %m
