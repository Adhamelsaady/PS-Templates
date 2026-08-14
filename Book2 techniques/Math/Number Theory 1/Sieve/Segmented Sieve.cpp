/*
 * Segmented Sieve
 *
 * What this file does:
 * Generates primes or prime-related arrays up to N.
 *
 * Typical problem to recognize:
 * Sieve of Eratosthenes marks multiples of each prime. Linear sieve generates each composite once through its smallest prime factor.
 *
 * Complexity / constraints:
 * Use segmented sieve when the upper bound is huge but the queried interval is short.
 *
 * Main variables:
 * N = maximum value; isPrime/composite = primality flags; lp = lowest prime factor; primes = list of primes.
 *
 * Variable guide for names used in this implementation:
 * L: left bound / LCM depending on function.
 * R: right bound.
 * lim: transform/precomputation limit.
 * i: loop index.
 * j: nested loop index.
 * primes: list of primes.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

vector<ll>Primes;
// Function: segmentedSieve(ll L, ll R).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<bool> segmentedSieve(ll L, ll R) {
    int lim = (int)sqrt(R);
    vector<bool> mark(lim + 1, true);
    vector<int> primes;//have primes [2 , sqrt(R)]
    for (ll i = 2; i <= lim; ++i) {
        if (mark[i]) {
            primes.emplace_back(i);
            for (ll j = i * i; j <= lim; j += i)
                mark[j] = false;
        }
    }

    vector<bool> isPrime(R - L + 1, true);
    for (long long i : primes) {
        for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
            isPrime[j - L] = false;
    }
    if (L == 1)
        isPrime[0] = false;
    for(int i = 0;i < R-L+1;i++){
        if(isPrime[i])Primes.emplace_back(i+L);
    }
    return isPrime;// the ith on the range prime or not   isPrime[i] represent L+i is prime or not
}
