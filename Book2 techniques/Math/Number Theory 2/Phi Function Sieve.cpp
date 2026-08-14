/*
 * Phi Function Sieve
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
 * N: maximum precomputation size.
 * phi: Euler totient values/result.
 * i: loop index.
 * j: nested loop index.
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
int phi[N];
// Function: totient().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void totient() {
  for (int i = 1; i < N; i++) phi[i] = i;
  for (int i = 2; i < N; i++) {
    if (phi[i] == i) {
      for (int j = i; j < N; j += i) phi[j] -= phi[j] / i;
    }
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  
  return 0;
}
