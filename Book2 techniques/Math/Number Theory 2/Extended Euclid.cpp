/*
 * Extended Euclid
 *
 * What this file does:
 * Finds gcd(a,b) and integers x,y such that ax+by=gcd(a,b).
 *
 * Typical problem to recognize:
 * Bézout coefficients are useful because when gcd(a,m)=1, x is a modular inverse of a modulo m.
 *
 * Complexity / constraints:
 * Core building block for modular inverse, CRT, and Diophantine equations.
 *
 * Main variables:
 * a,b = inputs; x,y = Bézout coefficients; g = gcd.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * d: divisor / gcd result / distance depending on function.
 * m: second size or modulus.
 * x: unknown or current value.
 * g: function/table array.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

using ll = long long;
// Function: extended_euclid(ll a, ll b, ll &x, ll &y).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1; y = 0;
    return a;
  }
  ll x1, y1;
  ll d = extended_euclid(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}
// Function: inverse(ll a, ll m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll inverse(ll a, ll m) {
  ll x, y;
  ll g = extended_euclid(a, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll x = 100, m = 37;
  cout << inverse(x, m) << '\n';
  return 0;
}
