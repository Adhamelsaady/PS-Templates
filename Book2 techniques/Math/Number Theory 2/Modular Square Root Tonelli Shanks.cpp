/*
 * Modular Square Root Tonelli Shanks
 *
 * What this file does:
 * Finds x such that x^2 = a (mod p) for prime p.
 *
 * Typical problem to recognize:
 * A quadratic residue is a number that has a square root modulo p.
 *
 * Complexity / constraints:
 * Tonelli-Shanks is the standard O(log^2 p) worst-case modular square-root algorithm.
 *
 * Main variables:
 * a = quadratic residue; p = odd prime; x = modular square root; q,s = decomposition of p-1.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * power: exponentiation helper/result.
 * n: main size/index/input value.
 * k: count/exponent/selected size.
 * mod: modulus.
 * ans: final or accumulated answer.
 * a: main input/base/coefficient.
 * p: prime/modulus/parameter depending on function.
 * r: chosen count / remainder / right bound.
 * x: unknown or current value.
 * b: second input/exponent/coefficient.
 * t: test case or temporary value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

// Function: power(long long n, long long k, const int mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int power(long long n, long long k, const int mod) {
  int ans = 1 % mod; n %= mod; if (n < 0) n += mod;
  while (k) {
    if (k & 1) ans = (long long) ans * n % mod;
    n = (long long) n * n % mod;
    k >>= 1;
  }
  return ans;
}
// find sqrt(a) % p, i.e. find any x such that x^2 = a (mod p)
// if a solution exist, then if a == 0 or p == 2, there are 1 solution, otherwise, there are exactly 2 solutions (x and p - x)
// p is prime
// complexity: O(log^2 p) worst case, O(log p) on average
// Function: SQRT(int a, int p).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int SQRT(int a, int p) {
  a %= p; if (a < 0) a += p;
  if (a == 0) return 0;
  if (power(a, (p - 1) / 2, p) != 1) return -1; // solution does not exist
  if (p % 4 == 3) return power(a, (p + 1) / 4, p);
  int s = p - 1, n = 2;
  int r = 0, m;
  while (s % 2 == 0) ++r, s /= 2;
  // find a non-square mod p
  while (power(n, (p - 1) / 2, p) != p - 1) ++n;
  int x = power(a, (s + 1) / 2, p);
  int b = power(a, s, p), g = power(n, s, p);
  for (;; r = m) {
    int t = b;
    for (m = 0; m < r && t != 1; ++m) t = 1LL * t * t % p;
    if (m == 0) return x;
    int gs = power(g, 1LL << (r - m - 1), p);
    g = 1LL * gs * gs % p;
    x = 1LL * x * gs % p;
    b = 1LL * b * g % p;
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int x, p; cin >> x >> p;
    cout << SQRT(x, p) << '\n';
  }
  return 0;
}
