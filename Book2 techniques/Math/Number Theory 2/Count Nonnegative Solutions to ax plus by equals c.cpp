/*
 * Count Nonnegative Solutions to ax plus by equals c
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
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * c: third coefficient/constant.
 * ans: final or accumulated answer.
 * k: count/exponent/selected size.
 * l: left bound / lower value.
 * f: function/table array.
 * e: prime exponent.
 * g: function/table array.
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

// number of integer solutions to ax + by <= c s.t. x, y >= 0
// number of nonnegative integer lattice points under or on the line ax + by = c
// Function: lattice_cnt(ll a, ll b, ll c).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll lattice_cnt(ll a, ll b, ll c) {
  assert(a >= 0 && b >= 0);
  if (c < 0) return 0;
  if (a == 0 or b == 0) {
    // infinite solutions
    assert(0);
    return -1;
  }
  assert(a > 0 && b > 0);
  if (a > b) swap(a, b);
  ll ans = 0;
  while (c >= 0) {
    ll k = b / a;
    ll l = b % a;
    ll f = c / b;
    ll e = c % b / a;
    ll g = c % b % a;
    ans += (f + 1) * (e + 1) + (f + 1) * f / 2 * k;
    c = f * l - a + g;
    b = a;
    a = l;
  }
  return ans;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << lattice_cnt(2, 3, 5) << '\n';
  return 0;
}
