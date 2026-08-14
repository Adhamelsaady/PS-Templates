/*
 * Floor Sum of Arithmetic Progression
 *
 * What this file does:
 * Computes sums involving floor((a*i+b)/m) without iterating over every i.
 *
 * Typical problem to recognize:
 * floor(x) is the greatest integer <= x. Floor-sum algorithms repeatedly swap numerator and modulus to shrink the problem.
 *
 * Complexity / constraints:
 * Usually O(log m) for the standard floor sum.
 *
 * Main variables:
 * n = number of terms; m = denominator/modulus; a,b = linear expression coefficients; ans = sum.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * a: main input/base/coefficient.
 * d: divisor / gcd result / distance depending on function.
 * m: second size or modulus.
 * res: accumulated result.
 * ans: final or accumulated answer.
 * k: count/exponent/selected size.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// Function: sumsq(ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll sumsq(ll n) {
  return n / 2 * ((n - 1) | 1);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) / m}, O(log m)
// Function: floor_sum(ll a, ll d, ll m, ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll floor_sum(ll a, ll d, ll m, ll n) {
  ll res = d / m * sumsq(n) + a / m * n;
  d %= m; a %= m;
  if (!d) return res;
  ll to = (n * d + a) / m;
  return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}
// \sum_{i = 0}^{n - 1}{(a + d * i) % m}
// Function: mod_sum(ll a, ll d, ll m, ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll mod_sum(ll a, ll d, ll m, ll n) {
  a = ((a % m) + m) % m;
  d = ((d % m) + m) % m;
  return n * a + d * sumsq(n) - m * floor_sum(a, d, m, n);
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  ll a, d, n; 
  while (cin >> a >> n >> d) {
    n = (n - a) / d;
    ll ans = 0;
    for (int k = 0; k < 32; k++) {
      ll cur = mod_sum(a, d, (1LL << k + 1), n + 1);
      cur -= mod_sum(a, d, (1LL << k), n + 1);
      if (cur / (1LL << k) & 1) {
        ans += 1LL << k;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
// http://poj.org/problem?id=3495
