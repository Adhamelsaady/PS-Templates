/*
 * Inverses from 1 to n
 *
 * What this file does:
 * Finds x such that a*x = 1 (mod m).
 *
 * Typical problem to recognize:
 * An inverse exists iff gcd(a,m)=1. For prime m, a^(m-2) is the inverse by Fermat’s little theorem.
 *
 * Complexity / constraints:
 * Extended Euclid works for any modulus when gcd is 1.
 *
 * Main variables:
 * a = number to invert; m = modulus; x/inv = inverse.
 *
 * Variable guide for names used in this implementation:
 * inv: modular inverses.
 * m: second size or modulus.
 * a: main input/base/coefficient.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

int inv[N];
// Function: ModInverse(int m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void ModInverse(int m){
//calculating the mod inverse for range [1,m-1] under module mod
    inv[1] = 1;
    for(int a = 2; a < m; ++a)
        inv[a] = mod - (long long)(mod/a) * inv[mod%a] % mod;
}
