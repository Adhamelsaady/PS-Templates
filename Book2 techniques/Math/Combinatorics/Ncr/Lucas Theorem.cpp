/*
 * Lucas Theorem
 *
 * What this file does:
 * Computes C(n,r) modulo a prime p when n may be much larger than p, using Lucas theorem.
 *
 * Typical problem to recognize:
 * Write n and r in base p, then multiply the small digit-wise binomials.
 *
 * Complexity / constraints:
 * Works when the modulus is prime.
 *
 * Main variables:
 * n = top of binomial; r = bottom; mod/p = prime modulus; fact/invfact = factorial tables modulo p.
 *
 * Variable guide for names used in this implementation:
 * fact: factorials.
 * inv: modular inverses.
 * InvFact: inverse factorials.
 * i: loop index.
 * n: main size/index/input value.
 * r: chosen count / remainder / right bound.
 * res: accumulated result.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

int fact[N];
int inv[N]; 
int InvFact[N];
// Function: init().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void init() {
    fact[0] = inv[1] = fact[1] = InvFact[0] = InvFact[1] = 1;
    for (long long i = 2; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
        inv[i] = mod - (inv[mod % i] * (mod / i) % mod);
        InvFact[i] = (inv[i] * InvFact[i - 1]) % mod;
    }
}
// Function: nCr(int n, int r).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int nCr(int n, int r) {
    if(r > n || n < 0 || r < 0) return 0;
    return (((fact[n] * InvFact[r]) % mod) * InvFact[n - r]) % mod;
}
// Function: lucas(int n , int r).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int lucas(int n , int r){
    if(r == 0) return 1;
    int res = 1;
    while(r){
        res = 1LL * res * nCr(n % mod , r % mod) % mod;
        n /= mod; r/= mod;
    }
    return res;
}
