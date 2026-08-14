/*
 * Linear Congruence Equation
 *
 * What this file does:
 * Solves ax = b (mod m).
 *
 * Typical problem to recognize:
 * A linear congruence is an equation where two integers are considered equal modulo m.
 *
 * Complexity / constraints:
 * A solution exists iff gcd(a,m) divides b.
 *
 * Main variables:
 * a,b,m = congruence coefficients/modulus; x = solution.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * d: divisor / gcd result / distance depending on function.
 * m: second size or modulus.
 * x: unknown or current value.
 * g: function/table array.
 * k: count/exponent/selected size.
 * ret: temporary/final return value.
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
// ax = b (mod m)
// Function: congruence_equation(ll a, ll b, ll m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<ll> congruence_equation(ll a, ll b, ll m) {
  vector<ll> ret;
  ll g = gcd(a, m), x;
  if (b % g != 0) return ret;
  a /= g, b /= g;
  x = inverse(a, m / g);
  for (int k = 0; k < g; ++k) { // exactly g solutions
    ret.push_back((x * b + m / g * k) % m);
  }
  return ret;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  auto ret = congruence_equation(4, 0, 12);
  for (auto x: ret) {
    cout << x << ' ';
  }
  return 0;
}
// https://cp-algorithms.com/algebra/linear_congruence_equation.html
