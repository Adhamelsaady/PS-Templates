/*
 * Chinese Remainder Theorem General
 *
 * What this file does:
 * Solves two congruences even when their moduli are not coprime, returning a solution modulo lcm(m1,m2) when the system is compatible.
 *
 * Typical problem to recognize:
 * Two congruences are compatible iff a1 == a2 (mod gcd(m1,m2)).
 *
 * Complexity / constraints:
 * O(log min(m1,m2)).
 *
 * Main variables:
 * a1,a2 = residues; m1,m2 = moduli; p,q = Bézout coefficients; g = gcd(m1,m2); x = merged residue.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * q: quotient or second input.
 * t: test case or temporary value.
 * p: prime/modulus/parameter depending on function.
 * g: function/table array.
 * m: second size or modulus.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

using T = __int128;
// ax + by = __gcd(a, b)
// returns __gcd(a, b)
// Function: extended_euclid(T a, T b, T &x, T &y).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
T extended_euclid(T a, T b, T &x, T &y) {
  T xx = y = 0;
  T yy = x = 1;
  while (b) {
    T q = a / b;
    T t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<T, T> CRT(T a1, T m1, T a2, T m2) {
  T p, q;
  T g = extended_euclid(m1, m2, p, q);
  if (a1 % g != a2 % g) return make_pair(0, -1);
  T m = m1 / g * m2;
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) %  m, m);
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << (int)CRT(1, 31, 0, 7).first << '\n';
  return 0;
}
