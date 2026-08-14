/*
 * Sum of Phi up to n
 *
 * What this file does:
 * Computes Euler’s totient φ(n), the number of integers in [1,n] coprime to n.
 *
 * Typical problem to recognize:
 * Coprime means gcd(a,n)=1. Euler phi is multiplicative for coprime arguments.
 *
 * Complexity / constraints:
 * Sieve versions compute φ for all numbers; single-number versions factor n.
 *
 * Main variables:
 * n = input; phi[i] = totient table; p = prime factor.
 *
 * Variable guide for names used in this implementation:
 * mod: modulus.
 * N: maximum precomputation size.
 * phi: Euler totient values/result.
 * n: main size/index/input value.
 * i: loop index.
 * j: nested loop index.
 * sum: running sum.
 * ans: final or accumulated answer.
 * t: test case or temporary value.
 * cnt: frequency/count array.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

const ll mod = 1e9 + 7, inv = (1e9 + 8) / 2;
 
const int N = 1e7;
ll phi[N + 1], pref[N + 1];
// Function: buildPhi(ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void buildPhi(ll n) {
    pref[1] = 1;
    for (ll i = 0; i <= n; i++) phi[i] = i;
    for (ll i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (ll j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
        pref[i] = pref[i - 1] + phi[i];
        if(pref[i] >= mod) pref[i] -= mod;
    }
}
 
unordered_map<ll, ll> dp;
// Function: sum(ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll sum(ll n) {
    if(n < N) return pref[n];
    if(dp.count(n)) return dp[n];
    ll at = 1, value = n;
    ll ans = (n%mod) * ((n + 1) % mod) % mod * inv % mod;
    while (at <= value) {
        ll t = value / at;
        ll nxt = value / t + 1;
        ll cnt = nxt - at;
        cnt %= mod;
        if(t != n) ans -= sum(t) * cnt % mod;
        if(ans < 0) ans += mod;
        at = nxt;
    }
    return dp[n] = ans;
}
 
