/*
 * Catalan using nCr
 *
 * What this file does:
 * Computes Catalan numbers. Catalan(n) counts many non-crossing structures: valid parenthesis sequences with n pairs, triangulations of an (n+2)-gon, non-crossing pairings, and more.
 *
 * Typical problem to recognize:
 * Catalan numbers are C_n = (1/(n+1)) * C(2n,n).
 *
 * Complexity / constraints:
 * Use the version matching your constraints: recursive for learning, iterative for a table, nCr for modular queries.
 *
 * Main variables:
 * n = Catalan index; catalan/C = stored answer.
 *
 * Variable guide for names used in this implementation:
 * inv: modular inverses.
 * i: loop index.
 * n: main size/index/input value.
 * r: chosen count / remainder / right bound.
 * ans: final or accumulated answer.
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
// Function: Catalan(int _n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int Catalan(int _n){
    return Ncr(2 * _n , _n) / (_n + 1);
}
// Function: init().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void init() {
    Inverse();
    FactorialInverse();
    factorial();
}
