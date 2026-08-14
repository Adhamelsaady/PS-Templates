/*
 * Fermat Primality Test
 *
 * What this file does:
 * Tests probable primality using Fermat’s little theorem.
 *
 * Typical problem to recognize:
 * For prime p and a not divisible by p, a^(p-1)=1 mod p.
 *
 * Complexity / constraints:
 * Fermat test is not deterministic because Carmichael composites can pass; prefer Miller-Rabin in contests.
 *
 * Main variables:
 * n = candidate; a = random/base witness.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * i: loop index.
 * a: main input/base/coefficient.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: probablyPrimeFermat(int n, int iter=100).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool probablyPrimeFermat(int n, int iter=100) {
    if (n < 4)
        return n == 2 || n == 3;

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (binpower(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
