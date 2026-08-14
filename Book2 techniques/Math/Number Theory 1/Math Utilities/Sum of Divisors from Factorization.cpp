/*
 * Sum of Divisors from Factorization
 *
 * What this file does:
 * Computes number/sum/product of divisors using prime factorization.
 *
 * Typical problem to recognize:
 * If n=product p^e, then number of divisors is product(e+1), and the sum of divisors is product(1+p+...+p^e).
 *
 * Complexity / constraints:
 * These formulas are the standard bridge from factorization to divisor queries.
 *
 * Main variables:
 * n = input; p = prime; e = exponent; ans = divisor function result.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * mod: modulus.
 * res: accumulated result.
 * ans: final or accumulated answer.
 * x: unknown or current value.
 * k: count/exponent/selected size.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

const ll MOD = 1000000007LL;

// Function: modpow(ll a, ll b, ll mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll modpow(ll a, ll b, ll mod) {
    a %= mod;
    if (a < 0) a += mod;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = ( (__int128)res * a ) % mod;
        a = ( (__int128)a * a ) % mod;
        b >>= 1;
    }
    return res;
}

// Function: modinv(ll a, ll mod).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll modinv(ll a, ll mod) {
    return modpow(a, mod - 2, mod);
}

// Function: sumDivisors(const vector<pair<ll,ll>>& factors).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll sumDivisors(const vector<pair<ll,ll>>& factors) {
    ll ans = 1;
    for (auto &p : factors) {
        ll x = p.first % MOD;
        ll k = p.second;
        if (x == 1) {
            ans = (ans * ((k + 1) % MOD)) % MOD;
        } else {
            ll numerator = (modpow(x, k + 1, MOD) - 1 + MOD) % MOD;
            ll denom_inv = modinv((x - 1 + MOD) % MOD, MOD);
            ll term = ( (__int128)numerator * denom_inv ) % MOD;
            ans = (ans * term) % MOD;
        }
    }
    return ans;
}
