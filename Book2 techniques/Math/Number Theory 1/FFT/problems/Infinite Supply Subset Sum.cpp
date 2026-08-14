/*
 * Infinite Supply Subset Sum
 *
 * What this file does:
 * Multiplies polynomials / computes convolution in O(N log N).
 *
 * Typical problem to recognize:
 * Convolution combines all pairs with the same index sum: c[k]=sum a[i]b[k-i].
 *
 * Complexity / constraints:
 * Use when O(N^2) pair counting is too slow.
 *
 * Main variables:
 * a,b = input coefficient arrays; fa/fb = transformed arrays; n = transform size; w/root = roots of unity.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * e: prime exponent.
 * r: chosen count / remainder / right bound.
 * n: main size/index/input value.
 * i: loop index.
 * k: count/exponent/selected size.
 * j: nested loop index.
 * N: maximum precomputation size.
 * rev: bit-reversal indices.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
// Function: PRE().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
static const int MOD = 998244353;
static const int ROOT = 3;
 
// Function: modexp(long long a, long long e).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int modexp(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return (int)r;
}
 
// Function: ntt(vector<int>& a, bool invert).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void ntt(vector<int>& a, bool invert) {
    int n = a.size();
    static vector<int> rev;
    static vector<int> roots{0,1};
 
    if ((int)rev.size() != n) {
        rev.assign(n,0);
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i>>1] >> 1) | ((i&1) * (n>>1));
    }
    for (int i = 0; i < n; i++)
        if (i < rev[i]) swap(a[i], a[rev[i]]);
 
    if ((int)roots.size() < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            // z is 2^{k+1}th root of unity
            int e = modexp(ROOT, (MOD-1) >> (k+1));
            for (int i = 1 << (k-1); i < (1<<k); i++) {
                roots[2*i] = roots[i];
                roots[2*i+1] = (int)((1LL*roots[i] * e) % MOD);
            }
            k++;
        }
    }
 
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += 2*len) {
            for (int j = 0; j < len; j++) {
                int u = a[i+j];
                int v = (int)((1LL * a[i+j+len] * roots[len+j]) % MOD);
                a[i+j] = u + v < MOD ? u + v : u + v - MOD;
                a[i+j+len] = u - v >= 0 ? u - v : u - v + MOD;
            }
        }
    }
    if (invert) {
        reverse(a.begin() + 1, a.end());
        int inv_n = modexp(n, MOD-2);
        for (int &x : a) x = (int)(1LL * x * inv_n % MOD);
    }
}
 
// Function: convolution(const vector<int>& a, const vector<int>& b, int max_size).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<int> convolution(const vector<int>& a, const vector<int>& b, int max_size) {
    int need = min((int)a.size() + (int)b.size() - 1, max_size);
    int n = 1;
    while (n < need) n <<= 1;
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = (int)(1LL * fa[i] * fb[i] % MOD);
    ntt(fa, true);
    fa.resize(need);
    return fa;
}
 
// Function: poly_pow(vector<int> base, long long exp, int max_size).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<int> poly_pow(vector<int> base, long long exp, int max_size) {
    vector<int> result(1, 1);
    while (exp > 0) {
        if (exp & 1) {
            result = convolution(result, base, max_size);
        }
        base = convolution(base, base, max_size);
        exp >>= 1;
    }
    return result;
}
const int N = 1e6 + 1;
int main(){
    PRE();
    int n , k;cin >> n >> k;
    vector<int>v(n);
    for (int i = 0;i < n;i++) cin >> v[i];
    vector<int>dp(N , 0);
    for (auto &val : v) dp[val] = 1;
    dp = poly_pow(dp , k , N);
    // for (int j = 0;j < k;j++) {
    //     bitset<N>ndp;
    //     for (int i = 0;i < n;i++) {
    //         ndp = ndp | (dp << v[i]);
    //     }
    //     swap(dp , ndp);
    // }
    for (int i = 1;i <= N;i++) {
        if (dp[i]) cout << i << " ";
    }
    cout << '\n';
}
