/*
 * Pollard Rho
 *
 * What this file does:
 * Factors large integers using Pollard Rho together with fast modular multiplication and prime testing helpers.
 *
 * Typical problem to recognize:
 * Pollard Rho finds a nontrivial factor of a composite number by looking for a collision modulo an unknown factor.
 *
 * Complexity / constraints:
 * Randomized; very fast in practice for 64-bit factorization when paired with Miller-Rabin.
 *
 * Main variables:
 * n = number being factored; x/y = pseudo-random sequence values; c = polynomial constant; d = discovered gcd factor; primes/spf = small-prime sieve arrays.
 *
 * Variable guide for names used in this implementation:
 * primes: list of primes.
 * x: unknown or current value.
 * y: unknown or current value.
 * m: second size or modulus.
 * res: accumulated result.
 * n: main size/index/input value.
 * c: third coefficient/constant.
 * i: loop index.
 * j: nested loop index.
 * cnt: frequency/count array.
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

using ll = long long;
namespace PollardRho {
  mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
  const int P = 1e6 + 9;
  ll seq[P];
  int primes[P], spf[P];
  // Function: add_mod(ll x, ll y, ll m).
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  inline ll add_mod(ll x, ll y, ll m) {
    return (x += y) < m ? x : x - m;
  }
  // Function: mul_mod(ll x, ll y, ll m).
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  inline ll mul_mod(ll x, ll y, ll m) {
    ll res = __int128(x) * y % m;
    return res;
    // ll res = x * y - (ll)((long double)x * y / m + 0.5) * m;
    // return res < 0 ? res + m : res;
  }
  // Function: pow_mod(ll x, ll n, ll m).
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  inline ll pow_mod(ll x, ll n, ll m) {
    ll res = 1 % m;
    for (; n; n >>= 1) {
      if (n & 1) res = mul_mod(res, x, m);
      x = mul_mod(x, x, m);
    }
    return res;
  }
  // O(it * (logn)^3), it = number of rounds performed
  // Function: miller_rabin(ll n).
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  inline bool miller_rabin(ll n) {
    if (n <= 2 || (n & 1 ^ 1)) return (n == 2);
    if (n < P) return spf[n] == n;
    ll c, d, s = 0, r = n - 1;
    for (; !(r & 1); r >>= 1, s++) {}
    // each iteration is a round
    for (int i = 0; primes[i] < n && primes[i] < 32; i++) {
      c = pow_mod(primes[i], r, n);
      for (int j = 0; j < s; j++) {
        d = mul_mod(c, c, n);
        if (d == 1 && c != 1 && c != (n - 1)) return false;
        c = d;
      }
      if (c != 1) return false;
    }
    return true;
  }
  // Function: init().
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  void init() {
    int cnt = 0;
    for (int i = 2; i < P; i++) {
      if (!spf[i]) primes[cnt++] = spf[i] = i;
      for (int j = 0, k; (k = i * primes[j]) < P; j++) {
        spf[k] = primes[j];
        if (spf[i] == spf[k]) break;
      }
    }
  }
  // returns O(n^(1/4))
  // Function: pollard_rho(ll n).
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  ll pollard_rho(ll n) {
    while (1) {
      ll x = rnd() % n, y = x, c = rnd() % n, u = 1, v, t = 0;
      ll *px = seq, *py = seq;
      while (1) {
        *py++ = y = add_mod(mul_mod(y, y, n), c, n);
        *py++ = y = add_mod(mul_mod(y, y, n), c, n);
        if ((x = *px++) == y) break;
        v = u;
        u = mul_mod(u, abs(y - x), n);
        if (!u) return __gcd(v, n);
        if (++t == 32) {
          t = 0;
          if ((u = __gcd(u, n)) > 1 && u < n) return u;
        }
      }
      if (t && (u = __gcd(u, n)) > 1 && u < n) return u;
    }
  }
  // Function: factorize(ll n).
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  vector<ll> factorize(ll n) {
    if (n == 1) return vector <ll>();
    if (miller_rabin(n)) return vector<ll> {n};
    vector <ll> v, w;
    while (n > 1 && n < P) {
      v.push_back(spf[n]);
      n /= spf[n];
    }
    if (n >= P) {
      ll x = pollard_rho(n);
      v = factorize(x);
      w = factorize(n / x);
      v.insert(v.end(), w.begin(), w.end());
    }
    return v;
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  PollardRho::init();
  int t; cin >> t;
  while (t--) {
    ll n; cin >> n;
    auto f = PollardRho::factorize(n);
    sort(f.begin(), f.end());
    cout << f.size() << ' '; 
    for (auto x: f) cout << x << ' '; cout << '\n';
  }
  return 0;
}
// https://judge.yosupo.jp/problem/factorize
