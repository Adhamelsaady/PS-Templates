/*
 * Count Nondecreasing Arrays
 *
 * What this file does:
 * Counts nondecreasing arrays/sequences using combinations.
 *
 * Typical problem to recognize:
 * Stars and bars counts ways to distribute identical items into bins.
 *
 * Complexity / constraints:
 * Check the function signature before applying it to a different sequence constraint.
 *
 * Main variables:
 * n = length; r/values = number of available values or chosen positions depending on the function.
 *
 * Variable guide for names used in this implementation:
 * inv: modular inverses.
 * i: loop index.
 * n: main size/index/input value.
 * r: chosen count / remainder / right bound.
 * ans: final or accumulated answer.
 * l: left bound / lower value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

int inv[N] , FInv[N] , fact[N];
// Function: Inverse().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void Inverse() {
    inv[0] = inv[1] = 1;
    for (int i = 2; i < N; i++)
        inv[i] = inv[mod % i] * (mod - mod / i) % mod;
}
// Function: FactorialInverse().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void FactorialInverse() {
    FInv[0] = FInv[1] = 1;
    for (int i = 2; i < N; i++)
        FInv[i] = (inv[i] * FInv[i - 1]) % mod;
}
// Function: factorial().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void factorial() {
    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
}
// Function: Ncr(int n, int r).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int Ncr(int n, int r) {
    int ans = ((fact[n] * FInv[r])
               % mod * FInv[n - r])
              % mod;
    return ans;
}
// Function: init().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void init() {
    Inverse();
    FactorialInverse();
    factorial();
}
// Function: Count(int n , int l ,int r).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int Count(int n , int l ,int r) {
    return add(-1, Ncr(n + r - l + 1, n), mod);
}
