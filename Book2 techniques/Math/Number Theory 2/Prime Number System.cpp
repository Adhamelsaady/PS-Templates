/*
 * Prime Number System
 *
 * What this file does:
 * Works with a representation based on prime factors/exponents.
 *
 * Typical problem to recognize:
 * Prime factorization gives a unique coordinate system for positive integers: each coordinate is a prime exponent.
 *
 * Complexity / constraints:
 * Use for multiplicative constraints, gcd/lcm, and divisibility.
 *
 * Main variables:
 * n = number; p/e = prime and exponent components.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * i: loop index.
 * j: nested loop index.
 * power: exponentiation helper/result.
 * n: main size/index/input value.
 * k: count/exponent/selected size.
 * ans: final or accumulated answer.
 * f: function/table array.
 * primes: list of primes.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 9, mod = 1e9 + 7;

int spf[N];
vector<int> primes;
// Function: linear_sieve().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void linear_sieve() {
  for(int i = 2; i < N; i++) {
    if (spf[i] == 0) spf[i] = i, primes.push_back(i);
    int sz = primes.size();
    for (int j = 0; j < sz && i * primes[j] < N && primes[j] <= spf[i]; j++) {
      spf[i * primes[j]] = primes[j];
    }
  }
}
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
struct base { // doesn't support zero
  map<int, int> mp;
  base() {}
  base(int n) {
    while (n > 1) {
      int k = spf[n], cnt = 0;
      while (n % k == 0) {
        n /= k;
        cnt++;
      }
      mp[k] = cnt;
    }
  }
  base(map<int, int> z) {
    mp = z;
  }
  // Function: val().
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  int val() {
    int ans = 1;
    for (auto x: mp) {
      assert(x.second >= 0);
      ans = 1LL * ans * power(x.first, x.second) % mod;
    }
    return ans;
  }
  // Function: pow(int k).
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  base pow(int k) {
    map<int, int> ans = mp;
    for (auto &x: ans) {
      x.second *= k;
    }
    return base(ans);
  }
  // Function: sqrt().
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  base sqrt() {
    map<int, int> ans = mp;
    for (auto &x: ans) {
      assert(x.second % 2 == 0);
      x.second /= 2;
    }
    return base(ans);
  }  
  base operator * (base p) {
    map<int, int> ans = mp;
    for (auto x: p.mp) {
      ans[x.first] += x.second;
    }
    return base(ans);
  }
  base operator / (base p) {
    map<int, int> ans = mp;
    for (auto x: p.mp) {
      ans[x.first] -= x.second;
    }
    return base(ans);
  }
  base& operator *= (base p) {
    return *this = (*this) * p;
  }  
  base& operator /= (base p) {
    return *this = (*this) / p;
  }
  // Function: print().
  // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
  void print() {
    bool f = 0;
    for (auto x: mp) {
      if (x.second) {
        f = 1;
        cout << "(" << x.first << ' ' << x.second << ") ";
      }
    }
    if (!f) {
      cout << 1;
    }
    cout << '\n';
  }
};
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  linear_sieve();
  base a = base(10), b = base(15);
  a *= a;
  a = a.sqrt();
  cout << a.val();
  return 0;
}
