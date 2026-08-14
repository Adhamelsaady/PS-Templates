/*
 * Sum of Two Squares Test
 *
 * What this file does:
 * Tests whether an integer can be written as x^2+y^2.
 *
 * Typical problem to recognize:
 * Fermat’s theorem: every prime p=3 mod 4 must have an even exponent in n for n to be a sum of two squares.
 *
 * Complexity / constraints:
 * Useful for number representation and lattice-point problems.
 *
 * Main variables:
 * n = target; p/e = prime factor/exponent.
 *
 * Variable guide for names used in this implementation:
 * p: prime/modulus/parameter depending on function.
 * res: accumulated result.
 * a: main input/base/coefficient.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include <bits/stdc++.h>
using namespace std;

#define FR FermatRepresent
namespace FermatRepresent {
    template<class num_t>
    // Function: mult(num_t a, num_t b, num_t p).
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    inline num_t mult(num_t a, num_t b, num_t p) {
        num_t q = (num_t) ((long double) a * b / p);
        num_t r = a * b - q * p;
        while (r < 0) r += p;
        while (r >= p) r -= p;
        return r;
    }
    template<class num_t>
    // Function: fpow(num_t n, num_t k, num_t p).
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    inline num_t fpow(num_t n, num_t k, num_t p) {
        num_t r = 1;
        for (; k; k >>= 1) {
            if (k & 1) r = mult(r, n, p);
            n = mult(n, n, p);
        }
        return r;
    }
    template<class num_t>
    // Function: isqrt(num_t k).
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    inline num_t isqrt(num_t k) {
        num_t r = sqrt(k) + 1;
        while (r * r > k) r--;
        return r;
    }
    // Function: func(long long p).
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    long long func(long long p) {
        srand(2311);
        while (1) {
            long long u = (long long) rand() * rand() % p;
            if (fpow(u, (p - 1) / 2, p) == p - 1) {
                long long res = fpow(u, (p - 1) / 4, p);
                return max(res, p - res);
            }
        }
    }
    // given an odd prime p
    // returns (a, b) s.t. a^2 + b^2 = p
    // p % 4 = 1, otherwise no solution exists
    pair<int, int> calc(long long p) {
        long long a = p, b = func(p);
        long long ip = isqrt(p);
        while (b > ip) {
            a %= b;
            swap(a, b);
        }
        return make_pair(b, isqrt(p - b * b));
    }
}

int main() {
    pair<int, int> res = FR::calc(613);
    cerr << res.first << " " << res.second << "\n";
    cerr << res.first * res.first + res.second * res.second << "\n";
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
