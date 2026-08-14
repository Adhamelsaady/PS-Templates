/**
 * Numerical real-root finder for a polynomial.
// Evaluate polynomial a[0]+a[1]x+... using Horner method in O(n).
 *
 * eval() uses Horner's rule. bisection() finds a root inside an interval where
 * the polynomial changes sign. solve() scans [-30,30] with step 0.5 and applies
 * bisection to every sign-changing interval.
 *
 * This is an approximate, specialized solver; roots outside the range or roots
 * of even multiplicity may not be detected reliably.
 */
#include <bits/stdc++.h>

using namespace std;
#define int long long
#define ld long double

ld eval(const vector<ld> &a, ld x) {
    ld res = 0;
    for (int i = a.size() - 1; i >= 0; --i)
        res = res * x + a[i];
    return res;
// Locate a real root in [l,r] assuming a sign change (or an endpoint root).
}

ld bisection(const vector<ld> &a, ld l, ld r) {
    ld fl = eval(a, l), fr = eval(a, r);
    for (int i = 0; i < 200; ++i) { // enough for precision
        ld m = (l + r) / 2;
        ld fm = eval(a, m);
        if (fl * fm <= 0) {
            r = m;
            fr = fm;
        } else {
            l = m;
            fl = fm;
        }
    }
    return (l + r) / 2;
// Scan a fixed real interval and use bisection on every sign-changing subinterval.
}

void solve() {
    // O((r - l) / step) * n * log((r - l) / e))
    int n;
    cin >> n;

    vector<ld> a(n + 1);
    for (int i = 0; i <= n; ++i)
        cin >> a[i];

    const ld step = 0.5, range = 30;
    vector<ld> roots;
    for (ld x = -range; x <= range; x += step) {
        ld f1 = eval(a, x);
        ld f2 = eval(a, x + step);
        if (f1 * f2 <= 0) {
            ld root = bisection(a, x, x + step);
            roots.push_back(root);
        }
    }

    sort(roots.begin(), roots.end());
    roots.erase(unique(roots.begin(), roots.end(), [](ld x, ld y) {
        return fabs(x - y) < 1e-6;
    }), roots.end());

    for (ld r: roots)
        cout << r << " ";
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef HALZOOM
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    int test = 1;
    cin >> test;

    for (int i = 1; i <= test; ++i) {
        cout << fixed << setprecision(8);
        solve();
    }
    return 0;
}