/*
 * Modular Inverse for Prime Modulus
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
 * a: main input/base/coefficient.
 * m: second size or modulus.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: ModInverse(int a,int m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int ModInverse(int a,int m){
    return fast_power(a,m-2,m);
}
