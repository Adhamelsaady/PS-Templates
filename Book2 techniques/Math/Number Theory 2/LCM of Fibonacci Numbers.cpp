/*
 * LCM of Fibonacci Numbers
 *
 * What this file does:
 * Computes F_n quickly, usually in O(log n), including modulo a given number.
 *
 * Typical problem to recognize:
 * Fast doubling uses identities for F(2k) and F(2k+1) to halve the index each step.
 *
 * Complexity / constraints:
 * Useful when n is up to 1e18 or larger.
 *
 * Main variables:
 * n = index; a,b = consecutive Fibonacci values during doubling; mod = modulus.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * power: exponentiation helper/result.
 * n: main size/index/input value.
 * k: count/exponent/selected size.
 * ans: final or accumulated answer.
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * i: loop index.
 * c: third coefficient/constant.
 * res: accumulated result.
 * dp: dynamic programming table.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod= 1e9 + 7;

// Function: power(long long n, long long k).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int power(long long n, long long k) {
  int ans = 1 % mod; n %= mod; if (n < 0) n += mod;
  while (k) {
    if (k & 1) ans = (long long) ans * n % mod;
    n = (long long) n * n % mod;
    k >>= 1;
  }
  return ans;
}
// Function: fib(long long n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int fib(long long n) {
  assert (n >= 0);
  if (n <= 1) return n;
  int a = 0;
  int b = 1;
  long long i = 1ll << (63 - __builtin_clzll(n) - 1);
  for (; i; i >>= 1) {
    int na = (a *(long long) a + b *(long long) b) % mod;
    int nb = (2ll * a + b) * b % mod;
    a = na;
    b = nb;
    if (n & i) {
      int c = a + b; if (c >= mod) c -= mod;
      a = b;
      b = c;
    }
  }
  return b;
}
map<vector<int>, int> dp;
/**
O((max number of divisors of a[i]) * n * log(max a[i])) but faster in practice
lcm(a1, a2, ... an) 
= lcm(lcm(a1, ..., a[n-1]), an)
= lcm(a1, ..., a[n-1]) * an / gcd(lcm(a1, ..., a[n-1]), an)
= lcm(a1, ..., a[n-1]) * an / lcm(gcd(a1, an), ... gcd(a[n-1], an))
**/
// Function: yo(vector<int> a).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int yo(vector<int> a) {
  sort(a.rbegin(), a.rend());
  while (!a.empty() && a.back() <= 2) a.pop_back();
  a.resize(unique(a.begin(), a.end()) - a.begin());
  if (a.empty()) return 1;
  if (a.size() == 1) return fib(a[0]);
  if (dp.count(a)) return dp[a];
  vector<int> b(a.begin(), a.end() - 1);
  long long res = yo(b);
  for (int i = 0; i < b.size(); ++i) b[i] = __gcd(b[i], a.back());
  res = res * fib(a.back()) % mod * power(yo(b), mod - 2) % mod;
  dp[a] = res;
  return res;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; cin >> n;
  vector<int> a(n);
  for (auto &x: a) cin >> x;
  cout << yo(a) << '\n';
  return 0;
}
//https://www.hackerrank.com/contests/infinitum10/challenges/fibonacci-lcm/problem
