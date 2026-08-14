/*
 * Linear Sieve
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
 * i: loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

int Lpf[N];
vector<int>LinearSieve(){
    for(int i=1;i<N;i++)Lpf[i]=i;
    vector<int>primes;
    for(int i=2 ;i<N;i++){
        if(Lpf[i]==i){
            primes.emplace_back(i);
        }
        for(auto &val:primes){
            if(i*val>=N)break;
            Lpf[i*val] = val;
        }
    }
    return primes;
}
