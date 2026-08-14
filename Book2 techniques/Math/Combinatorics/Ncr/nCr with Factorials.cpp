/*
 * nCr with Factorials
 *
 * What this file does:
 * Precomputes factorials and inverse factorials so C(n,r) can be answered in O(1) after O(N) preprocessing.
 *
 * Typical problem to recognize:
 * The binomial coefficient is n! / (r!(n-r)!), with division replaced by modular inverses.
 *
 * Complexity / constraints:
 * Requires a prime modulus and n < mod for the usual implementation.
 *
 * Main variables:
 * fact = i!; inv = modular inverse of i; FInv/invFact = inverse factorial; n,r = query.
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

ll inv[N] , FInv[N] , fact[N];
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
    if(r > n)return 0;
    ll ans = ((fact[n] * FInv[r])
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
