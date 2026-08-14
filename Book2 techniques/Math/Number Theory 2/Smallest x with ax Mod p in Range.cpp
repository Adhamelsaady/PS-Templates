/*
 * Smallest x with ax Mod p in Range
 *
 * What this file does:
 * Counts values or finds the smallest x for which a*x mod p lies in an interval.
 *
 * Typical problem to recognize:
 * Modulo p wraps integers into residues 0..p-1.
 *
 * Complexity / constraints:
 * Floor-sum methods avoid iterating over all x.
 *
 * Main variables:
 * a = multiplier; p = modulus; l,r = target interval; x = queried integer.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * q: quotient or second input.
 * t: test case or temporary value.
 * x: unknown or current value.
 * y: unknown or current value.
 * d: divisor / gcd result / distance depending on function.
 * m: second size or modulus.
 * f: function/table array.
 * p: prime/modulus/parameter depending on function.
 * l: left bound / lower value.
 * r: chosen count / remainder / right bound.
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

const int N = 1e9, mod = 1e9 + 7;

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

// find z such that z % x = a, z % y = b. 
// here, z is unique modulo M = lcm(x,y).
// returns (z, M). on failure, M = -1.
pair<T, T> CRT(T x, T a, T y, T b) {
  T s, t;
  T d = extended_euclid(x, y, s, t);
  if (a % d != b % d) return make_pair(0, -1);
  T m = x * y;
  s %= m; s = (s + m) % m;
  t %= m; t = (t + m) % m;
  return make_pair((s * b % m * x % m + t * a % m * y % m) %  m / d, m / d);
}

T cdiv(T x, T y) { return (x + y - 1) / y; }
// returns the smallest non-negative integer x s.t l <= a * x mod p <= r
// IMPORTANT : 0 <= a < p, 0 <= l <= r < p, p is not necessarily prime
// Complexity: O(log (p))
// Function: f(long long p, long long a, long long l, long long r).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
long long f(long long p, long long a, long long l, long long r) { 
  if (a == 0) return l == 0 ? 0 : -1;
  long long c = cdiv((T)l, (T)a); 
  if (a * c <= r) return c;
  long long b = p % a; // p = k * a + b, l <= a(x - k * y) - b * y <= r 
  // => -r <= b * y % a <= -l
  auto y = f(a, b, a - r % a, a - l % a); 
  return y == -1 ? y : cdiv(l + (T)b * y, a) + p / a * y;
}

const long long M = 1LL * mod * (mod + 2);
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    cout << "? " << mod << endl;
    int r1; cin >> r1;
    cout << "? " << mod + 2 << endl;
    int r2; cin >> r2;
    T x = CRT(mod, r1, mod + 2, r2).first;
    long long q = f(M, x, 1, N);
    long long p = x * q % M;
    cout << "! " << p << ' ' << q << endl;
  }
  return 0;
}
// https://codeforces.com/gym/102354/problem/I
