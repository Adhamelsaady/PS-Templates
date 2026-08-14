/*
 * Stirling First Kind Fixed k
 *
 * What this file does:
 * Computes Stirling numbers. Second-kind S(n,k) counts partitions of n distinct elements into k nonempty unlabeled groups. First-kind variants count permutations by cycles.
 *
 * Typical problem to recognize:
 * A set partition is a split into nonempty groups where group order does not matter.
 *
 * Complexity / constraints:
 * Use the exact first/second-kind file according to the problem.
 *
 * Main variables:
 * n = number of elements; k = number of groups/cycles.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * mod: modulus.
 * root: primitive root.
 * lim: transform/precomputation limit.
 * x: unknown or current value.
 * y: unknown or current value.
 * ans: final or accumulated answer.
 * i: loop index.
 * g: function/table array.
 * j: nested loop index.
 * k: count/exponent/selected size.
 * n: main size/index/input value.
 * f: function/table array.
 * a: main input/base/coefficient.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 1 << 18;
const int mod = 998244353;
const int root = 3;
int lim, rev[N], w[N], wn[N], inv_lim;
void reduce(int &x) { x = (x + mod) % mod; }
// Function: POW(int x, int y, int ans = 1).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int POW(int x, int y, int ans = 1) {
  for (; y; y >>= 1, x = (long long) x * x % mod) if (y & 1) ans = (long long) ans * x % mod;
  return ans;
}
// Function: precompute(int len).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void precompute(int len) {
  lim = wn[0] = 1; int s = -1;
  while (lim < len) lim <<= 1, ++s;
  for (int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
  const int g = POW(root, (mod - 1) / lim);
  inv_lim = POW(lim, mod - 2);
  for (int i = 1; i < lim; ++i) wn[i] = (long long) wn[i - 1] * g % mod;
}
// Function: ntt(vector<int> &a, int typ).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void ntt(vector<int> &a, int typ) {
  for (int i = 0; i < lim; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int i = 1; i < lim; i <<= 1) {
    for (int j = 0, t = lim / i / 2; j < i; ++j) w[j] = wn[j * t];
    for (int j = 0; j < lim; j += i << 1)
      for (int k = 0; k < i; ++k) {
        const int x = a[k + j], y = (long long) a[k + j + i] * w[k] % mod;
        reduce(a[k + j] += y - mod), reduce(a[k + j + i] = x - y);
      }
  }
  if (!typ) {
    reverse(a.begin() + 1, a.begin() + lim);
    for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * inv_lim % mod;
  }
}
// Function: multiply(vector<int> &f, vector<int> &g).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<int> multiply(vector<int> &f, vector<int> &g) {
  int n=(int)f.size() + (int)g.size() - 1;
  precompute(n);
  vector<int> a = f, b = g;
  a.resize(lim); b.resize(lim);
  ntt(a, 1), ntt(b, 1);
  for (int i = 0; i < lim; ++i) a[i] = (long long) a[i] * b[i] % mod;
  ntt(a, 0);
  //while((int)a.size() && a.back() == 0) a.pop_back();
  return a;
}
// a^k % x^n
// Function: power(vector<int> a, int k, int n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<int> power(vector<int> a, int k, int n) {
  assert(a.size() <= n);
  vector<int> ans({1});
  while (k) {
    if (k & 1) {
      ans = multiply(ans, a);
      ans.resize(n);
    }
    a = multiply(a, a);
    a.resize(n);
    k >>= 1;
  }
  return ans;
}
// returns stirling1st(i, k) for 0 <= i < n
// O(n log^2 n)
// Function: stirling(int n, int k).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<int> stirling(int n, int k) {
  assert(k <= n);
  vector<int> a(n); // sum c(i) / i! x^i, c(i) = (i - 1)!
  a[0] = 0;
  for (int i = 1; i < n; i++) {
    a[i] = POW(i, mod - 2);
  }
  auto ans = power(a, k, n);
  ans.resize(n);
  int f = 1;
  for (int i = 1; i <= k; i++) {
    f = 1LL * f * i % mod;
  }
  int cur = 1;
  // sum ans(i) / i! = 1 / k! * a^k
  for (int i = 0; i < n; i++) {
    ans[i] = 1LL * ans[i] * cur % mod;
    cur = 1LL * cur * (i + 1) % mod;
    ans[i] = 1LL * ans[i] * POW(f, mod - 2) % mod;
  }
  return ans;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int k = 3, n = 10;
  auto ans = stirling(n, k);
  for (int i = 0; i < n; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
// https://codeforces.com/blog/entry/77468
