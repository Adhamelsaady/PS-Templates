/*
 * Mobius Function
 *
 * What this file does:
 * Computes the Möbius function μ(n), used for Möbius inversion and exact-GCD counting.
 *
 * Typical problem to recognize:
 * μ(n)=0 if n has a squared prime factor; otherwise it is (-1)^(number of distinct prime factors).
 *
 * Complexity / constraints:
 * A common use is converting counts of multiples into counts of numbers with exact gcd.
 *
 * Main variables:
 * mu[n] = Möbius value; n = integer; d = divisor.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * i: loop index.
 * j: nested loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

const int N = 5e5 + 9;

int mob[N];
// Function: mobius().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void mobius() {
  mob[1] = 1;
  for (int i = 2; i < N; i++){
    mob[i]--;
    for (int j = i + i; j < N; j += i) {
      mob[j] -= mob[i];
    }
  }
}
