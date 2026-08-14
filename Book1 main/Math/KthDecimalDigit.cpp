/**
 * Modular-arithmetic helper for digits of a/b after the decimal point.
 *
 * The k-th digit after the decimal point can be obtained from the remainder of
// Find the first position (among the first b positions) whose digit equals c.
 * 10^(k-1) * a modulo b, avoiding construction of the huge decimal prefix.
 * The sample solve() searches the first b positions for a requested digit.
 */
#include <bits/stdc++.h>

using namespace std;
// Fast modular exponentiation: computes base^pow mod mod.
#define int long long

int exp(int base, int pow, int mod) {
    if (pow < 0)return 0;
    int res = 1;
    while (pow) {
        if (pow & 1) res = (res * base) % mod;
        base = (base * base) % mod, pow >>= 1;
    }
    return res;
}

// Return the k-th digit after the decimal point of a/b without constructing all
// previous digits.
// a / b
int KthDecDigit(int a, int b, int k) {
    int d = 10 * (a * exp(10, (k - 1) % b, b) % b) / b;
    return d;
}

void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    for (int i = 1; i <= b; ++i) {
        int d = KthDecDigit(a, b, i);
        if (d == c)
            return void(cout << i << '\n');
    }
    cout << "-1\n";

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef HALZOOM
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    int test = 1;
//    cin >> test;

    for (int i = 1; i <= test; ++i) {
        solve();
    }
    return 0;
}