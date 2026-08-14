/*
 * Sum of Divisors Counts up to n in Cube Root Time
 *
 * What this file does:
 * Computes number/sum/product of divisors using prime factorization.
 *
 * Typical problem to recognize:
 * If n=product p^e, then number of divisors is product(e+1), and the sum of divisors is product(1+p+...+p^e).
 *
 * Complexity / constraints:
 * These formulas are the standard bridge from factorization to divisor queries.
 *
 * Main variables:
 * n = input; p = prime; e = exponent; ans = divisor function result.
 *
 * Variable guide for names used in this implementation:
 * t: test case or temporary value.
 * n: main size/index/input value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

using uint32 = unsigned int;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

// credit: zimpha
// compute \sum_{i=1}^{n} sigma0(i) in ~O(n^{1/3}) time.
// it is also equal to \sum_{i=1}^{n} floor(n / i)
// takes ~100 ms for n = 1e18 
// Function: sum_sigma0(uint64 n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
uint128 sum_sigma0(uint64 n) {
  auto out = [n] (uint64 x, uint32 y) {
    return x * y > n;
  };
  auto cut = [n] (uint64 x, uint32 dx, uint32 dy) {
    return uint128(x) * x * dy >= uint128(n) * dx;
  };
  const uint64 sn = sqrtl(n);
  const uint64 cn = pow(n, 0.34); //cbrtl(n);
  uint64 x = n / sn;
  uint32 y = n / x + 1;
  uint128 ret = 0;
  stack<pair<uint32, uint32>> st;
  st.emplace(1, 0);
  st.emplace(1, 1);
  while (true) {
    uint32 lx, ly;
    tie(lx, ly) = st.top();
    st.pop();
    while (out(x + lx, y - ly)) {
      ret += x * ly + uint64(ly + 1) * (lx - 1) / 2;
      x += lx, y -= ly;
    }
    if (y <= cn) break;
    uint32 rx = lx, ry = ly;
    while (true) {
      tie(lx, ly) = st.top();
      if (out(x + lx, y - ly)) break;
      rx = lx, ry = ly;
      st.pop();
    }
    while (true) {
      uint32 mx = lx + rx, my = ly + ry;
      if (out(x + mx, y - my)) {
        st.emplace(lx = mx, ly = my);
      } 
      else {
        if (cut(x + mx, lx, ly)) break;
        rx = mx, ry = my;
      }
    }
  }
  for (--y; y > 0; --y) ret += n / y;
  return ret * 2 - sn * sn;
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t; cin >> t;
  while (t--) {
    long long n; cin >> n;
    auto ans = sum_sigma0(n);
    string s = "";
    while (ans > 0) {
      s += char('0' + ans % 10);
      ans /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << '\n';
  }
  return 0;
}
// https://www.spoj.com/problems/DIVCNT1/en/
