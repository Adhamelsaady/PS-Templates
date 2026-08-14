/*
 * Discrete Logarithm
 *
 * What this file does:
 * Finds x from a^x = b (mod m), typically with Baby-Step Giant-Step.
 *
 * Typical problem to recognize:
 * A discrete logarithm reverses modular exponentiation.
 *
 * Complexity / constraints:
 * Standard BSGS is about O(sqrt(m)) time and memory.
 *
 * Main variables:
 * a = base; b = target; m = modulus; x = discrete logarithm; step = block size.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * m: second size or modulus.
 * n: main size/index/input value.
 * i: loop index.
 * p: prime/modulus/parameter depending on function.
 * ans: final or accumulated answer.
 * q: quotient or second input.
 * d: divisor / gcd result / distance depending on function.
 * x: unknown or current value.
 * g: function/table array.
 * t: test case or temporary value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

// baby step - giant step
// returns minimum integer x such that a^x = b (mod m)
// a and m are co-prime
// Function: discrete_log(int a, int b, int m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int discrete_log(int a, int b, int m) {
  static const int inf = 2e9;
  int n = (int) sqrt (m + .0) + 1;
  int pw = 1;
  for (int i = 0; i < n; ++i) pw = 1LL * pw * a % m;
  gp_hash_table<int, int> vals;
  for (int p = 1, cur = pw; p <= n; ++p) {
    if (!vals[cur]) vals[cur] = p;
    cur = 1LL * cur * pw % m;
  }
  int ans = inf;
  for (int q = 0, cur = b; q <= n; ++q) {
    if (vals.find(cur) != vals.end()) {
      long long nw = 1LL * vals[cur] * n - q;
      if (nw < ans) ans = nw;
    }
    cur = (1LL * cur * a) % m;
  }
  if (ans == inf) ans = -1;
  return ans;
}
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
// discrete log but a and m may not be co-prime
// Function: discrete_log_noncoprime(int a, int b, int m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int discrete_log_noncoprime(int a, int b, int m) {
  if (m == 1) return 0;
  if (b == 1) return 0;
  if (__gcd(a, m) == 1) return discrete_log(a, b, m);
  int g = __gcd(a, m);
  if (b % g != 0)  return -1;
  int p = inverse(a / g, m / g);
  int nw = discrete_log_noncoprime(a, 1LL * b / g * p % (m / g), m / g);
  if (nw == -1) return -1;
  return nw + 1;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1000;
  while (t--) {
    int m = rand() % 100000 + 2, a = rand() % m + 1, b = rand() % m;
    cout << discrete_log_noncoprime(a, b, m) << '\n';
  }
  return 0;
}
