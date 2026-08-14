/*
 * Count Binary Grid Colorings
 *
 * What this file does:
 * Counts objects up to symmetry using Burnside’s lemma: average the number of configurations fixed by each symmetry.
 *
 * Typical problem to recognize:
 * Burnside says the number of distinct orbits equals (sum of fixed configurations over all group elements) / |group|.
 *
 * Complexity / constraints:
 * Use for rotations/reflections of grids, necklaces, colorings, and symmetric arrangements.
 *
 * Main variables:
 * n/m = size or number of colors; res = accumulated fixed configurations; mod = modulus.
 *
 * Variable guide for names used in this implementation:
 * mod: modulus.
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * res: accumulated result.
 * n: main size/index/input value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// 2 colors only
const int mod = 1e9 + 7;

// Function: binpow(ll a, ll b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll binpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    PRE();
    ll n;
    cin >> n;
    if (n & 1) {
        ll res = binpow(2, n * n) + 2 * (binpow(2, (n - 1) / 2 * (n + 1) / 2) * 2 + binpow(2, n * n / 2));
        res %= mod;
        cout << res * binpow(4, mod - 2) % mod << '\n';
    } else {
        ll res = binpow(2, n * n) + binpow(2, n * n / 4) * 2 + binpow(2, n * n / 2);
        res %= mod;
        cout << res * binpow(4, mod - 2) % mod << '\n';
    }
}
