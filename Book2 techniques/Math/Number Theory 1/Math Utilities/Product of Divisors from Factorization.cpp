/*
 * Product of Divisors from Factorization
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
 * k: count/exponent/selected size.
 * x: unknown or current value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

const ll MOD = 1000000007LL;
const ll MOD1 = 1000000006LL;

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

// Function: productDivisors(const vector<pair<ll,ll>>& orig_factors).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll productDivisors(const vector<pair<ll,ll>>& orig_factors) {
    vector<pair<ll,ll>> factors = orig_factors;
    ll num1 = 1;
    bool halvedOne = false;
    for (auto &p : factors) {
        ll k = p.second;
        if (!halvedOne && (k % 2 == 1)) {
            num1 = (num1 * (( (k + 1) / 2 ) % MOD1)) % MOD1;
            halvedOne = true;
        } else {
            num1 = (num1 * ((k + 1) % MOD1)) % MOD1;
        }
    }
    if (!halvedOne) {
        for (auto &p : factors) p.second /= 2;
    }
    ll number = 1;
    for (auto &p : factors) {
        ll x = p.first % MOD;
        ll k = p.second;
        number = ( (__int128)number * modpow(x, k, MOD) ) % MOD;
    }
    ll prod = modpow(number, num1, MOD);
    return prod;
}
