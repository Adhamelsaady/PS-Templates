/*
 * Mobius Function
 *
 * What this file does:
 * Computes the Möbius function μ(n), used for Möbius inversion and exact-GCD counting.
 *
 * Typical problem to recognize:
 * μ(n)=0 if n has a squared prime factor; otherwise it is (-1)^(number of distinct prime factors).
 *
 * Complexity / constraints:
 * A common use is converting counts of multiples into counts of numbers with exact gcd.
 *
 * Main variables:
 * mu[n] = Möbius value; n = integer; d = divisor.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * i: loop index.
 * j: nested loop index.
 * x: unknown or current value.
 * k: count/exponent/selected size.
 * ans: final or accumulated answer.
 * a: main input/base/coefficient.
 * n: main size/index/input value.
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

const int N = 5e5 + 9;

int mob[N];
// Function: mobius().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void mobius() {
  mob[1] = 1;
  for (int i = 2; i < N; i++){
    mob[i]--;
    for (int j = i + i; j < N; j += i) {
      mob[j] -= mob[i];
    }
  }
}
bool vis[N];
vector<int> d[N];
int mul[N];
// Function: add(int x, int k).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void add(int x, int k) {
  for (auto y: d[x]) {
    mul[y] += k;
  }
}
// Function: query(int x).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int query(int x) {
  int ans = 0;
  for (auto y: d[x]) {
    ans += mul[y] * mob[y];
  }
  return ans;
}
int a[N];
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  mobius();
  for (int i = 1; i < N; i++) {
    if (mob[i]) {
      for (int j = i; j < N; j += i) {
        d[j].push_back(i);
      }
    }
  }
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  long long ans = 0;
  while (q--) {
    int i; cin >> i;
    if (vis[i]) {
      ans -= query(a[i]);
      ans += a[i] == 1;
      add(a[i], -1);
    }
    else {
      ans += query(a[i]);
      add(a[i], 1);
    }
    vis[i] ^= 1;
    cout << ans << '\n';
  }
  return 0;
}
// https://codeforces.com/contest/547/problem/C
