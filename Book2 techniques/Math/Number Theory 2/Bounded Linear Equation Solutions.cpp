/*
 * Bounded Linear Equation Solutions
 *
 * What this file does:
 * Counts solutions to a linear equation with upper bounds on variables.
 *
 * Typical problem to recognize:
 * Upper bounds prevent plain stars-and-bars from applying directly; inclusion-exclusion is a common fix.
 *
 * Complexity / constraints:
 * Check whether the source uses a modulus and whether coefficients are positive.
 *
 * Main variables:
 * coefficients = equation values; upper = per-variable maximum; dp/ans = count.
 *
 * Variable guide for names used in this implementation:
 * mod: modulus.
 * k: count/exponent/selected size.
 * i: loop index.
 * j: nested loop index.
 * n: main size/index/input value.
 * mask: chosen subset bitmask.
 * x: unknown or current value.
 * t: test case or temporary value.
 * r: chosen count / remainder / right bound.
 * a: main input/base/coefficient.
 * ans: final or accumulated answer.
 * l: left bound / lower value.
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

template <const int32_t MOD>
struct modint {
  int32_t value;
  modint() = default;
  modint(int32_t value_) : value(value_) {}
  inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
  inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
  inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
  inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
  inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
  inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
  inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
  modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
  modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
  inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
  inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
  inline bool operator == (modint<MOD> other) const { return value == other.value; }
  inline bool operator != (modint<MOD> other) const { return value != other.value; }
  inline bool operator < (modint<MOD> other) const { return value < other.value; }
  inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> istream & operator >> (istream & in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

using poly = vector<mint>;

// Function: eval(poly a, mint x).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
mint eval(poly a, mint x) {
  mint ans = 0, p = 1;
  for (mint b : a) {
    ans += p * b;
    p *= x;
  }
  return ans;
}
poly operator + (poly a, poly b) {
  if (a.size() < b.size()) a.resize(b.size(), 0);
  for (int i = 0; i < b.size(); i++) {
    a[i] += b[i];
  }
  return a;
} 
poly operator - (poly a, poly b) {
  if (a.size() < b.size()) a.resize(b.size(), 0);
  for (int i = 0; i < b.size(); i++) {
    a[i] -= b[i];
  }
  return a;
}
poly operator * (poly a, poly b) {
  vector<mint> r(a.size() + b.size() - 1, 0);
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      r[i + j] += a[i] * b[j];
    }
  }
  return r;
}
vector<pair<long long, int>> get(vector<long long> a) {
  int n = a.size();
  vector<pair<long long, int>> ans;
  for (int mask = 0; mask < (1 << n); mask++) {
    long long add = 0; int x = 1;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        add += a[i];
        x = -x;
      }
    }
    ans.push_back({add, x});
  }
  return ans;
}
// (x + n)(x + n - 1)...(x + n - k + 1);
// Function: falling(long long n, int k).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
poly falling(long long n, int k) {
  poly ans({1});
  mint p = n % mod;
  for (int i = 0; i < k; i++) {
    ans = ans * poly({p - i, 1});
  }
  return ans;
}
// returns the number of solutions to the equation x_0 + ... + x_(n-1) = s s.t. 0 <= x_i <= a_i
// O(2^(n/2)*n^2)
// Function: yo(vector<long long> a, long long s).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
mint yo(vector<long long> a, long long s) {
  int n = a.size();
  for (auto &x: a) ++x;
  vector<long long> l, r;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) l.push_back(a[i]);
    else r.push_back(a[i]);
  }
  auto L = get(l);
  auto R = get(r);
  sort(L.begin(), L.end());
  sort(R.rbegin(), R.rend());
  int i = 0;
  poly f({0});
  mint ans = 0;
  for (auto [x, y]: R) {
    while (i < L.size() and L[i].first + x <= s) {
      if (L[i].second == 1) f = f + falling(s + n - 1 - L[i].first, n - 1);
      else f = f - falling(s + n - 1 - L[i].first, n - 1);
      ++i;
    }
    ans += eval(f, (-x % mod + mod) % mod) * y;
  }
  for (int i = 1; i <= n - 1; i++) {
    ans /= i;
  }
  return ans;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<long long> a(n);
    long long s = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      --a[i];
      s += a[i];
    }
    s /= 2;
    cout << yo(a, s) << '\n';
  }
  return 0;
}
// https://codeforces.com/gym/102114/problem/F
