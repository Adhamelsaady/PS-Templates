/*
 * Fast Fibonacci
 *
 * What this file does:
 * Computes F_n quickly, usually in O(log n), including modulo a given number.
 *
 * Typical problem to recognize:
 * Fast doubling uses identities for F(2k) and F(2k+1) to halve the index each step.
 *
 * Complexity / constraints:
 * Useful when n is up to 1e18 or larger.
 *
 * Main variables:
 * n = index; a,b = consecutive Fibonacci values during doubling; mod = modulus.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * mod: modulus.
 * a: main input/base/coefficient.
 * i: loop index.
 * c: third coefficient/constant.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

// Function: fib(long long n, int mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int fib(long long n, int mod) {
  assert (n >= 0);
  if (n <= 1) return n;
  int a = 0, b = 1;
  long long i = 1ll << (63 - __builtin_clzll(n) - 1);
  for (; i; i >>= 1) {
    int na = (a *(long long) a + b *(long long) b) % mod;
    int nb = (2ll * a + b) * b % mod;
    a = na; b = nb;
    if (n & i) {
      int c = a + b; if (c >= mod) c -= mod;
      a = b; b = c;
    }
  }
  return b;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fib(10, 100) << '\n';
  return 0;
}
