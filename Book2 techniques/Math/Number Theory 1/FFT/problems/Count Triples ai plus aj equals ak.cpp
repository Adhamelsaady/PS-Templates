/*
 * Count Triples ai plus aj equals ak
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
 * n: main size/index/input value.
 * i: loop index.
 * j: nested loop index.
 * N: maximum precomputation size.
 * ans: final or accumulated answer.
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
}
using cd = complex<double>;
const double PI = acos(-1);
// Function: FFT(vector<cd> & a, bool invert).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void FFT(vector<cd> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1 , 0);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}
// Function: multiply(vector<ll> const& a, vector<ll> const& b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    FFT(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    while (result.size() != a.size() + b.size() - 1) result.pop_back();
    return result;
}

const int N = 5e4 + 10;
int main(){
    PRE();
    int n;cin >> n;
    vector<ll>poly1(N * 4 + 10);
    vector<int>a(n);
    ll zeros = 0;
    for (int i = 0;i < n;i++) {
        cin >> a[i];
        if (!a[i]) zeros++;
        poly1[a[i] + N]++;
    }
    auto res = multiply(poly1 , poly1);

    for (int i = 0;i < n;i++) {
        res[a[i] + a[i] + 2 * N]--;
    }

    // now res have all pairs sums , res[i + N] => number of pairs (i != j) where sum of those pairs is i
    ll ans = 0;
    for (auto &val : a) {
        ans += res[val + 2 * N];
    }
    ans -= 1LL * 2 * zeros * (n - 1);
    cout << ans << '\n';
}
