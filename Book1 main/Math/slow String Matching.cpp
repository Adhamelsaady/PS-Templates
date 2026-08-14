/**
 * FFT-based string matching for a small alphabet (A,C,T,G).
 *
 * For each character, build a 0/1 indicator array for the text and reversed
 * pattern. Their convolution counts how many positions match that character.
 * Summing over the four characters gives the number of matches at every shift.
 * The answer printed here is the minimum Hamming distance between the pattern
 * and any substring of the text.
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long

using cd = complex<double>;
const double PI = acos(-1);

// Standard iterative FFT.
// Fast Fourier Transform
void fft(vector<cd> &a, bool invert) {
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
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd &x : a)
            x /= n;
    }
}

// Integer polynomial convolution using FFT.
// Multiply two integer polynomials using FFT
vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + (int)b.size())
        n <<= 1;

    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
// Run one convolution for each DNA character A/C/G/T and accumulate matches.
}

void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    string T = "ACTG";
    vector<int> match(n + 1);

    for (auto c : T) {
        vector<int> a(n + 5), b(m + 5);
        for (int i = 0; i < n; ++i)
            a[i] = (s[i] == c);
        for (int i = 0; i < m; ++i)
            b[m - i] = (t[i] == c);

        auto res = multiply(a, b);
        for (int i = 0; i <= n - m; ++i)
            match[i] += res[i + m];
    }

    int answer = 1e9;
    for (int i = 0; i <= n - m; ++i)
        answer = min(answer, m - match[i]);

    cout << answer;
}
