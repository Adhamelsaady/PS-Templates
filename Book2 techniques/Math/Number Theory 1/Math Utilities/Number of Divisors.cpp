/*
 * Number of Divisors
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
 * i: loop index.
 * e: prime exponent.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: numberOfDivisors(long long num).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
long long numberOfDivisors(long long num) {
    long long total = 1;
    for (int i = 2; (long long)i * i <= num; i++) {
        if (num % i == 0) {
            int e = 0;
            do {
                e++;
                num /= i;
            } while (num % i == 0);
            total *= e + 1;
        }
    }
    if (num > 1) {
        total *= 2;
    }
    return total;
}
//d(p*q) = d(p)*d(q)
