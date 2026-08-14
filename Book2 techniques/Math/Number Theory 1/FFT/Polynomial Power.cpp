/*
 * Polynomial Power
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
 * N: maximum precomputation size.
 * n: main size/index/input value.
 * i: loop index.
 * k: count/exponent/selected size.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// remember to limit the size to what you want
const int N = 1e6 + 5;
using cd = complex<double>;
const double PI = acos(-1);
// Function: fft(vector<cd> & a, bool invert).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1 , 0), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
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

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
        if(result[i] > 1)result[i] = 1;
    }
    return result;
}

// Function: fp(vector<ll>&ans, vector<ll>&base, int k).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void fp(vector<ll>&ans, vector<ll>&base, int k) {
    while (k) {
        if(k % 2)
            ans = multiply(ans, base);
        // while (ans.size() > N)
        //     ans.pop_back();
        k /= 2;
        base = multiply(base, base);
        while (base.size() > N)
            base.pop_back();
    }
}
