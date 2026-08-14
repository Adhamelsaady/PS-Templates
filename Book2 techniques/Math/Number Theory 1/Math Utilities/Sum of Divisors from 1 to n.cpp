/*
 * Sum of Divisors from 1 to n
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
 * sum: running sum.
 * n: main size/index/input value.
 * res: accumulated result.
 * i: loop index.
 * l: left bound / lower value.
 * r: chosen count / remainder / right bound.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: sum(__int128 n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
__int128 sum(__int128 n){
   return n * ( n + 1 ) / 2;
}
// Function: S(__int128 n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
__int128 S(__int128 n){
    __int128 res = 0;
    for(__int128 i=1;i*i<=n;i++){
        __int128 l = i, r = n/i;
        res = res + i*(r-l+1) + sum(r) - sum(l);
        res %= mod;
    }
    return res;
}
// Function: RangeSum(__int128 l,__int128 r).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
__int128 RangeSum(__int128 l,__int128 r){
    return add(S(r)  , - S(l-1) , mod);
}
