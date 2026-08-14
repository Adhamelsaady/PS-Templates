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
 * N: maximum precomputation size.
 * i: loop index.
 * j: nested loop index.
 * primes: list of primes.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9;

int spf[N];
vector<int> primes;
// Function: sieve().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void sieve() {
  for(int i = 2; i < N; i++) {
    if (spf[i] == 0) spf[i] = i, primes.push_back(i);
    int sz = primes.size();
    for (int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++) {
      spf[i * primes[j]] = primes[j];
    }
  }
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  return 0;
}
