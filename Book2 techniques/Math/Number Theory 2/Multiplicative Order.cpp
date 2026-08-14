/*
 * Multiplicative Order
 *
 * What this file does:
 * Finds the smallest k>0 with a^k = 1 (mod m).
 *
 * Typical problem to recognize:
 * The multiplicative order is the period of powers of a in the modular multiplicative group.
 *
 * Complexity / constraints:
 * Usually factor φ(m) and repeatedly divide candidate order.
 *
 * Main variables:
 * a = base; m = modulus; order = smallest exponent.
 *
 * Variable guide for names used in this implementation:
 * power: exponentiation helper/result.
 * n: main size/index/input value.
 * k: count/exponent/selected size.
 * mod: modulus.
 * res: accumulated result.
 * ans: final or accumulated answer.
 * i: loop index.
 * a: main input/base/coefficient.
 * m: second size or modulus.
 * t: test case or temporary value.
 * x: unknown or current value.
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
// Function: power(ll n, ll k, const ll mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll power(ll n, ll k, const ll mod) {
  ll res = 1;
  while (k) {
    if (k & 1) res = __int128(res) * n % mod;
    n = __int128(n) * n % mod;
    k >>= 1;
  }
  return res;
}
// Function: totient(ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll totient(ll n) {
  ll ans = n;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      ans = ans / i * (i - 1);
    }
  }
  if (n > 1) ans = ans / n * (n - 1);
  return ans;
}
// returns the minimum positive k s.t. a^ k = 1 modulo mod. On failure, returns -1
// we just have to check the divisors of phi(mod) as candidates of k (Lagranges Theorem)
// which can still be optimized further. Check: https://cp-algorithms.com/algebra/primitive-root.html#toc-tgt-3
// it always exists if a and mod are coprime
// O((log(mod)^2)) + sqrt(mod) for calculating totient
// it can still be optimized. Check: https://brilliant.org/wiki/carmichaels-lambda-function/
// Function: multiplicative_order(ll a, ll mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll multiplicative_order(ll a, ll mod) {
  if (__gcd(a, mod) != 1) return -1;
  ll m = totient(mod), p = m;
  ll ans = 2e18;
  if (power(a, p, mod) == 1) ans = p;
  vector<ll> fac;
  for (ll i = 2 ; i * i <= m; i++) {
    if (m % i == 0) {
      while(m % i == 0) m /= i, fac.push_back(i);
    }
  }
  if (m > 1) fac.push_back(m);
  for (auto x: fac) {
    if (power(a, p / x, mod) == 1) p /= x, ans = p;
  }
  assert(ans != 2e18);
  return ans;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    ll x, m; cin >> x >> m;
    ll nw = x, st = x;
    ll mul = 1;
    while (x > 0){
      x /= 10;
      mul *= 10;
    }
    m *= mul - 1;
    m /= __gcd(m, st);
    ll ans = multiplicative_order(mul, m);
    cout << ans << '\n';
  }
  return 0;
}
// https://toph.co/p/i-am-good
