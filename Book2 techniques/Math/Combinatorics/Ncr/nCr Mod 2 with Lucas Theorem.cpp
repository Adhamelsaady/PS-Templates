/*
 * nCr Mod 2 with Lucas Theorem
 *
 * What this file does:
 * Answers C(n,r) modulo 2 using Lucas theorem in base 2. The result is 1 exactly when every 1-bit of r is also a 1-bit of n.
 *
 * Typical problem to recognize:
 * Lucas theorem reduces a huge binomial modulo a prime to digit-wise small binomials.
 *
 * Complexity / constraints:
 * O(number of bits).
 *
 * Main variables:
 * n = total elements; r = chosen elements.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * i: loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: Ncr(int n , int i).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool Ncr(int n , int i) {
    // Ncr(n , i) % 2 = 1 if every bit of i is less than or equal to the corresponding bit of n
    return !(i & ~(n - 1));
}
