/*
 * Nonnegative Solutions to ax plus by equals c
 *
 * What this file does:
 * Counts nonnegative integer solutions of ax+by=c or related equations.
 *
 * Typical problem to recognize:
 * Nonnegative means x,y are integers >= 0.
 *
 * Complexity / constraints:
 * After finding one solution, all solutions form an arithmetic progression; bounds determine the count.
 *
 * Main variables:
 * a,b,c = coefficients; x,y = nonnegative unknowns; ans = number of solutions.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * i: loop index.
 * k: count/exponent/selected size.
 * l: left bound / lower value.
 * r: chosen count / remainder / right bound.
 * ans: final or accumulated answer.
 * d: divisor / gcd result / distance depending on function.
 * a: main input/base/coefficient.
 * q: quotient or second input.
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
const ll inf = 1e18;

struct LDE { // sum(a[i] * x[i]) = k, x[i] >= 0
  int n, x;
  vector<ll> d;
  LDE() {}
  LDE(vector<int> a) { // O(min(a[i]) * n * log(min(a[i])))
    n = a.size();
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    x = *min_element(a.begin(), a.end());
    assert(x > 0);
    d.resize(x);
    fill(d.begin(), d.end(), inf);
    d[0] = 0; q.push(pair<ll, int>(0, 0));
    while (!q.empty()) {
      pair<ll, int> nw = q.top(); q.pop();
      int u = nw.second;
      ll val = nw.first;
      if (d[u] != val) continue;
      for (int i = 0; i < n; ++ i) {
        ll tmp = val + a[i];
        int v = tmp % x;
        if (d[v] > tmp) {
          d[v] = tmp;
          q.push(pair<ll, int>(tmp, v));
        }
      }
    }
  }
  bool can(ll k) { // if a solution exists
    return d[k % x] <= k;
  }
  ll count(ll l, ll r) { // count of l <= k <= r s.t. solution for k exists
    ll ans = 0;
    for (int i = 0; i < x; i++) { // d[i], d[i] + x, d[i] + 2 * x, ... are achievable
      ans += d[i] <= r ? (r - d[i]) / x + 1 : 0;
      ans -= d[i] <= l - 1 ? (l - 1 - d[i]) / x + 1: 0;
    }
    return ans;
  }
};
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n; ll l, r; cin >> n >> l >> r;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  LDE t(a);
  cout << t.count(l, r) << '\n';
  return 0;
}
// https://www.lydsy.com/JudgeOnline/problem.php?id=2118
// https://codeforces.com/blog/entry/71230?#comment-556761
