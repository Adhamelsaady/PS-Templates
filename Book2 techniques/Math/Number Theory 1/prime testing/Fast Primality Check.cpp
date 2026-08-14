/*
 * Fast Primality Check
 *
 * What this file does:
 * Deterministic 64-bit Miller-Rabin primality test using modular multiplication with __int128.
 *
 * Typical problem to recognize:
 * A Miller-Rabin witness can prove that n is composite; using a known deterministic witness set makes the test exact for 64-bit integers.
 *
 * Complexity / constraints:
 * O(number of witnesses * log n).
 *
 * Main variables:
 * n = number to test; a = witness; d = odd part of n-1; s = exponent of 2 in n-1; x = modular power result.
 *
 * Variable guide for names used in this implementation:
 * r: chosen count / remainder / right bound.
 * a: main input/base/coefficient.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

using u64 = uint64_t;
using u128 = __uint128_t;

// Function: binpower(u64 base, u64 e, u64 mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

// Function: check_composite(u64 n, u64 a, u64 d, int s).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};
// Function: MillerRabin(u64 n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool MillerRabin(u64 n) {
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}
