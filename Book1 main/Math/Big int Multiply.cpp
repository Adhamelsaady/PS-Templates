/**
 * Multiplication and exponentiation of very large non-negative decimal
 * integers represented as strings.
 *
 * mul_two_big_int converts decimal digits to polynomial coefficients and uses
 * an external FFT multiply() to perform convolution. Carry propagation then
 * turns the convolution coefficients back into decimal digits.
 *
 * IMPORTANT: this file expects multiply(vector<int>, vector<int>) from FFT.cpp
 * (or another compatible implementation) to be available.
 */
#include<bits/stdc++.h>
using namespace std;
// Multiply two decimal strings by treating their digits as polynomial coefficients
// and using FFT convolution supplied by another template.
#define int long long

string mul_two_big_int(const string &s1, const string &s2) {
    int n = s1.size(), m = s2.size();
    vector<int> poly1(n), poly2(m);
    for (int i = 0; i < n; ++i) { poly1[n - i - 1] = s1[i] - '0'; }
    for (int i = 0; i < m; ++i) { poly2[m - i - 1] = s2[i] - '0'; }
    vector<int> ans = multiply(poly1, poly2);  // using FFT
    int k = ans.size();
    for (int i = 0; i < k - 1; ++i) {
        ans[i + 1] += ans[i] / 10;
        ans[i] = ans[i] % 10;
    }
    string final = to_string(ans[k - 1]);
    for (int i = k - 2; i >= 0; --i) { final += (char) (ans[i] + '0'); }
    for (int i = 0; i < k; ++i) {
        if (final[i] != '0') return final.substr(i);
    }
    return "0";
// Binary exponentiation where each multiplication is big-integer multiplication.
}

string power_of_big_int(string s, int p) {
    string ans = "1";
    while (p) {
        if (p & 1) ans = mul_two_big_int(ans, s);
        s = mul_two_big_int(s, s);
        p >>= 1;
    }
    return ans;
}