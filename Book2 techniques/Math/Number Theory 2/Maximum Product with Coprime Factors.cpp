/*
 * Maximum Product with Coprime Factors
 *
 * What this file does:
 * Factorizes integers into primes, using trial division for small values or Pollard Rho for 64-bit values.
 *
 * Typical problem to recognize:
 * Prime factorization writes n as a product of prime powers.
 *
 * Complexity / constraints:
 * Use Miller-Rabin + Pollard Rho for n up to 64-bit.
 *
 * Main variables:
 * n = number to factor; p = prime factor; cnt/exponent = its multiplicity; factors = result.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * cnt: frequency/count array.
 * b: second input/exponent/coefficient.
 * x: unknown or current value.
 * ret: temporary/final return value.
 * i: loop index.
 * a: main input/base/coefficient.
 * j: nested loop index.
 * n: main size/index/input value.
 * ans: final or accumulated answer.
 * d: divisor / gcd result / distance depending on function.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const int N = 1e5;

// credit: mango_lassi
int arr[N + 1];
int u[N + 1];
int cnt[N + 1];

vector<int> d[N + 1];
bool b[N + 1];

// Function: coprime(int x).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool coprime(int x) {
  int ret = 0;
  for (int i : d[x]) ret += cnt[i] * u[i];
  return ret;
}

// Function: update(int x, int a).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void update(int x, int a) {
  for (int i : d[x]) cnt[i] += a;
}

int main() {
  for (int i = 1; i <= N; i++) {
    for (int j = i; j <= N; j += i) d[j].push_back(i);
    if (i == 1) u[i] = 1;
    else if ((i / d[i][1]) % d[i][1] == 0) u[i] = 0;
    else u[i] = -u[i / d[i][1]];
  }

  int n;
  cin >> n;

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    ans = max(ans, (ll)a);
    b[a] = 1;
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 2; i * j <= N; ++j) b[i] |= b[i * j];
  }

  vector<int> s;
  for (int i = N; i > 0; --i) {
    if (! b[i]) continue;
    while(coprime(i)) {
      ans = max(ans, (ll)i * s.back());
      update(s.back(), -1);
      s.pop_back();
    }
    update(i, 1);
    s.push_back(i);
  }
  cout << ans << '\n';
}
// https://codeforces.com/contest/1285/submission/68564248
