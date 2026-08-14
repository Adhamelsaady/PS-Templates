/*
 * Power Tower Modulo m
 *
 * What this file does:
 * Evaluates a^b^c^... modulo m recursively, reducing exponents with Euler phi/Carmichael-style reasoning.
 *
 * Typical problem to recognize:
 * A power tower is right-associative: a^(b^(c^...)).
 *
 * Complexity / constraints:
 * Exponent reduction requires coprimality or a careful non-coprime handling; read the source assumptions.
 *
 * Main variables:
 * a = current base; exponent/tower = remaining tower; m = modulus.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * phi: Euler totient values/result.
 * n: main size/index/input value.
 * ans: final or accumulated answer.
 * i: loop index.
 * x: unknown or current value.
 * m: second size or modulus.
 * power: exponentiation helper/result.
 * k: count/exponent/selected size.
 * mod: modulus.
 * a: main input/base/coefficient.
 * l: left bound / lower value.
 * r: chosen count / remainder / right bound.
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

const int N = 1e5 + 9;
using ll = long long;

map<ll, ll> mp;
// Function: phi(ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll phi(ll n) {
  if (mp.count(n)) return mp[n];
  ll ans = n, m = n;
  for (ll i = 2; i * i <= m; i++) {
    if (m % i == 0) {
      while (m % i == 0) m /= i;
      ans = ans / i * (i - 1);
    }
  }
  if (m > 1) ans = ans / m * (m - 1);
  return mp[n] = ans;
}
// Function: MOD(ll x, ll m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
inline ll MOD(ll x, ll m) {
  if (x < m) return x;
  return x % m + m;
}
// Function: power(ll n, ll k, ll mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll power(ll n, ll k, ll mod) {
  ll ans = MOD(1, mod);
  while (k) {
    if (k & 1) ans = MOD(ans * n, mod);
    n = MOD(n * n, mod);
    k >>= 1;
  }
  return ans;
}
int a[N];
// if x >= log2(m), then a^x = a^(MOD(x, phi(m))) % m
// Function: yo(ll l, ll r, ll m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll yo(ll l, ll r, ll m) {
  if (l == r) return MOD(a[l], m);
  if (m == 1) return 1;
  return power(a[l], yo(l + 1, r, phi(m)), m); 
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  int q; cin >> q;
  while (q--) {
    int l, r; cin >> l >> r;
    cout << yo(l, r, m) % m << '\n';
  }
  return 0;
}
// https://codeforces.com/contest/906/problem/D
