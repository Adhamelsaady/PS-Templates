#include <bits/stdc++.h>

using namespace std;
#define int long long

/*
    ============================================================
    Combinatorics Toolkit
    ============================================================

    This file contains common counting formulas used in CP:
      - nCr: choose r elements from n (order does NOT matter)
      - nPr: choose r elements from n (order DOES matter)
      - Stars and Bars: distribute identical objects into boxes
      - Catalan numbers: balanced parentheses, BSTs, triangulations, etc.
      - Lucas theorem: nCr when n/r are huge and MOD is a small prime
      - nCr parity: whether C(n,r) is odd
      - Pascal triangle construction

    Main idea:
      Precompute factorials and inverse factorials so that nCr/nPr
      queries can be answered in O(1) after O(N) preprocessing.
*/

const int mod = 1e9 + 7, N = 2e6 + 6;

struct Combinatorics {
    vector<int> fact, inv;

    // Precompute:
    // fact[i] = i! mod MOD
    // inv[i]  = 1 / i! mod MOD (inverse factorial)
    //
    // After this preprocessing, nCr/nPr are O(1).
    Combinatorics(int n) {
        fact.assign(n + 1, 1);
        inv.assign(n + 1, 1);

        for (int i = 1; i <= n; ++i)
            fact[i] = (fact[i - 1] * i) % mod;

        // fact[i + 1] = fact[i] * (i + 1);
        // invfact[i]  = invfact[i + 1] * (i + 1);
        // Compute inverse of n!, then walk backwards to get all inverse factorials.
        inv[n] = modInv(fact[n]);
        for (int i = n - 1; i >= 0; --i)
            inv[i] = (inv[i + 1] * (i + 1)) % mod;
    }

    // Modular inverse using Fermat's Little Theorem:
    // a^(-1) = a^(MOD-2) mod MOD, because MOD is prime.
    int modInv(int n) { return exp(n, mod - 2); }

    // Fast modular exponentiation: base^pow mod MOD.
    int exp(int base, int pow) {
        if (pow < 0) return 0;

        int res = 1;
        while (pow) {
            if (pow & 1)
                res = (res * base) % mod;
            base = (base * base) % mod;
            pow >>= 1;
        }
        return res;
    }

    // Compute C(n,r) = n! / (r! (n-r)!) mod MOD.
    // Use when 0 <= r <= n and n <= preprocessing limit.
    int nCr(int n, int r) {
        if (r == 0) return 1;
        if (r < 0 or n < r) return 0;
        return fact[n] * inv[n - r] % mod * inv[r] % mod;
    }

    // Compute P(n,r) = n! / (n-r)! mod MOD.
    // Order matters here.
    int nPr(int n, int r) {
        if (r < 0 or n < r) return 0;
        return fact[n] * inv[n - r] % mod;
    }

    // Stars and Bars:
    // Number of non-negative integer solutions to
    //     x1 + x2 + ... + xm = n
    // is C(n+m-1, m-1), which equals C(n+m-1, m).
    //
    // Typical problem: distribute n identical objects among m boxes.
    int starsABars(int n, int m) {
        return nCr(n + m - 1, m);
    }

    // Catalan number:
    //     Cat(n) = C(2n,n) / (n+1)
    //
    // Common applications:
    //   - balanced parentheses
    //   - number of BSTs with n keys
    //   - triangulations of polygons
    //   - non-crossing structures
    int Catalan(int n) {
        return modInv(n + 1) * nCr(2 * n, n) % mod;
    }

    // Generalized Catalan / Fuss-Catalan-like form used by this template:
    //     (k+1)/(n+k+1) * C(2n+k,n)
    //
    // Use only when the problem's combinatorial derivation gives this exact formula.
    int Catalan(int n, int k) {
        return (k + 1) * modInv(n + k + 1) % mod * nCr(2 * n + k, n) % mod;
    }
} comb(N);

// Lucas Theorem:
// Compute C(n,r) mod p when n and r may be huge and p is a prime.
//
// Write n and r in base p:
//   n = n0 + n1*p + n2*p^2 + ...
//   r = r0 + r1*p + r2*p^2 + ...
// Then:
//   C(n,r) = product C(ni,ri) mod p.
//
// IMPORTANT: the factorial table must support values below p.
// The current global comb table is sized for N, so this implementation is
// only directly safe when the needed base-p digits are <= N-1.
int lucas(int n, int r) {
    int answer = 1;

    while (n or r) {
        int A = n % mod;
        int B = r % mod;

        answer = answer * comb.nCr(A, B) % mod;
        n /= mod;
        r /= mod;
    }

    return answer;
}

// C(n,r) is odd iff r is a submask of n.
// Equivalent condition:
//     (n & r) == r
//
// This is a consequence of Lucas' theorem modulo 2.
// Example: C(5,2)=10 is even because 101 & 010 != 010.
int nCr_Parity(int n, int r) {
    if (n < r) return 0;
    return (n & r) == r;
}

// Exact-ish C(n,k) using floating point.
// This is convenient for small/moderate n when the answer fits in int64,
// but it is NOT the preferred method for large exact answers because
// floating-point precision can be lost.
int C(int n, int k) {
    long double res = 1;
    for (int i = 1; i <= k; ++i)
        res = res * (n - k + i) / i;

    return (int) (res + 0.01);
}

// Build the complete Pascal triangle up to row n.
// C[i][j] = C(i,j), using Pascal's recurrence:
//     C(i,j) = C(i-1,j-1) + C(i-1,j)
//
// Useful when n is small and you need many binomial coefficients at once.
vector<vector<int>> Pascal(int n) {
    vector<vector<int>> C(n + 1, vector<int>(n + 1));
    C[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int k = 1; k < i; ++k)
            C[i][k] = C[i - 1][k - 1] + C[i - 1][k];
    }

    return C;
}
