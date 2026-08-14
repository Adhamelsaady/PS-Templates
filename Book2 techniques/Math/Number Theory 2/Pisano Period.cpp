/*
 * Pisano Period
 *
 * What this file does:
 * Finds/uses the period of Fibonacci numbers modulo m.
 *
 * Typical problem to recognize:
 * The Pisano period is the length of the repeating Fibonacci sequence modulo m.
 *
 * Complexity / constraints:
 * Useful to reduce a huge Fibonacci index before computing modulo m when the period is manageable.
 *
 * Main variables:
 * m = modulus; period = cycle length; n = Fibonacci index.
 *
 * Variable guide for names used in this implementation:
 * mod: modulus.
 * power: exponentiation helper/result.
 * n: main size/index/input value.
 * k: count/exponent/selected size.
 * ans: final or accumulated answer.
 * primes: list of primes.
 * x: unknown or current value.
 * y: unknown or current value.
 * m: second size or modulus.
 * res: accumulated result.
 * c: third coefficient/constant.
 * i: loop index.
 * j: nested loop index.
 * cnt: frequency/count array.
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * p: prime/modulus/parameter depending on function.
 * t: test case or temporary value.
 * d: divisor / gcd result / distance depending on function.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
using ll = long long;
// Function: power(ll n, ll k, const ll mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll power(ll n, ll k, const ll mod) {
  ll ans = 1 % mod; n %= mod;
  while (k) {
    if (k & 1) ans = __int128(ans) * n % mod;
    n = __int128(n) * n % mod;
    k >>= 1;
  }
  return ans;
}
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
// Function: fib(ll n, ll mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll fib(ll n, ll mod) {
  if (n <= 1) return n;
  ll a = 0;
  ll b = 1;
  ll i = 1ll << (63 - __builtin_clzll(n) - 1);
  for (; i; i >>= 1) {
    ll na = (__int128(a) * a % mod + __int128(b) * b % mod) % mod;
    ll nb = __int128(2ll * a + b) * b % mod;
    a = na;
    b = nb;
    if (n & i) {
      ll c = a + b; if (c >= mod) c -= mod;
      a = b;
      b = c;
    }
  }
  return b;
}
// Function: pisano_period_prime(ll p).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll pisano_period_prime(ll p) {
  if (p == 2) return 3;
  if (p == 5) return 20;
  ll x = p % 5 == 1 or p % 5 == 4 ? p - 1 : 2 * p + 2;
  auto v = PollardRho::factorize(x);
  map<ll, int> mp;
  for (auto x: v) {
    mp[x]++;
  }
  vector<ll> d;
  d.push_back(1);
  for (auto [p, e]: mp) {
    ll cur = 1;
    int sz = d.size();
    for (int i = 0; i < e; i++) {
      cur *= p;
      for (int j = 0; j < sz; j++) {
        d.push_back(d[j] * cur);
      }
    }
  }
  sort(d.begin(), d.end());
  for (auto x: d) {
    if (fib(x, p) == 0 and fib(x + 1, p) == 1) {
      return x;
    }
  }
  assert(0);
  return -1;
}
// returns pisano period of n i.e. the period with which the sequence of Fibonacci numbers taken modulo n repeats
// Function: pisano_period(ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll pisano_period(ll n) {
  auto v = PollardRho::factorize(n);
  map<ll, int> mp;
  for (auto x: v) {
    mp[x]++;
  }
  ll ans = 1;
  for (auto [p, e]: mp) {
    ll cur = pisano_period_prime(p);
    for (int i = 1; i < e; i++) {
      cur *= p;
    }
    ans = ans / __gcd(ans, cur) * cur;
  }
  return ans;
}
// returns k s.t. fib(i * k) (for i >= 0) are the only fib numbers which are divisible by n
// Function: divisor_gap(ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll divisor_gap(ll n) {
  ll k = pisano_period(n);
  if (k % 4 == 0 and fib(k / 4, n) == 0) return k / 4;
  if (k % 2 == 0 and fib(k / 2, n) == 0) return k / 2;
  return k;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  PollardRho::init();
  int t; cin >> t;
  while (t--) {
    ll a, b, n; cin >> a >> b >> n;
    ll k = divisor_gap(n);
    ll ans = power(a, b, mod) - power(a, b, k) % mod;
    ans = (ans + mod) % mod;
    ans = ans * power(k, mod - 2, mod);
    ans = (ans + 1) % mod;
    cout << ans << '\n';
  }
  return 0;
}
// https://www.spoj.com/problems/DIVFIBS2/
