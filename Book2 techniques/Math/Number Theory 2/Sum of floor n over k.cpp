/*
 * Sum of floor n over k
 *
 * What this file does:
 * Computes sum_{k=1..n} floor(n/k) by grouping equal quotients.
 *
 * Typical problem to recognize:
 * Quotient grouping: floor(n/i) has the same value for a whole interval of i, so all indices in that interval can be processed at once.
 *
 * Complexity / constraints:
 * O(sqrt(n)) time.
 *
 * Main variables:
 * n = upper bound; i = first index in a quotient block; last = last index with the same floor(n/i); sum = accumulated answer.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * sum: running sum.
 * i: loop index.
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

// \sum{k=1}^{n}{floor(n/k)}
// count of numbers such that n/i = k -> n/k - n/(k+1)
// Function: floor_sum(ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll floor_sum(ll n) {
  ll sum = 0;
  for (ll i = 1, last; i <= n; i = last + 1) {
    last = n / (n / i);
    sum += (n / i) * (last - i + 1);
    // n / x yields the same value for i <= x <= last.
  }
  return sum;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  return 0;
}
