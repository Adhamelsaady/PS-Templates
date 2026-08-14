/*
 * Basic Sieve
 *
 * What this file does:
 * Generates primes or prime-related arrays up to N.
 *
 * Typical problem to recognize:
 * Sieve of Eratosthenes marks multiples of each prime. Linear sieve generates each composite once through its smallest prime factor.
 *
 * Complexity / constraints:
 * Use segmented sieve when the upper bound is huge but the queried interval is short.
 *
 * Main variables:
 * N = maximum value; isPrime/composite = primality flags; lp = lowest prime factor; primes = list of primes.
 *
 * Variable guide for names used in this implementation:
 * i: loop index.
 * j: nested loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

bool Prime[N];
// Function: sieve().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void sieve() {
    for(int i=2;i<N;i++){
        Prime[i]=true;
    }
    for (int i = 2; i*i < N; i++) {
        if(Prime[i]) {
            for (int j = i * i; j < N; j += i) {
                Prime[j] = false;
            }
        }
    }
}
