/*
 * Highest Composite Power in Factorial
 *
 * What this file does:
 * Finds the largest exponent e such that k^e divides n!. For prime k this is Legendre’s formula; for composite k it checks each prime factor.
 *
 * Typical problem to recognize:
 * v_p(n!) is the number of times prime p appears in the factorization of n!.
 *
 * Complexity / constraints:
 * Useful for trailing zeros, divisibility of factorials, and prime-power constraints.
 *
 * Main variables:
 * n = factorial argument; k = base whose power is requested; res = maximum valid exponent.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * k: count/exponent/selected size.
 * res: accumulated result.
 * j: nested loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: cal(int n, int k).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int cal (int n, int k) {
    int res = 0;
    //return largest x such that pow(k , x) | n!
    while (n) {
        n /= k;
        res += n;
    }
    return res;
}
// Function: factorial_power(int n,int k).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int factorial_power(int n,int k) {
    int res = inf;
    for (int j = 2; j * j <= k; j++) {
        if (k % j == 0) {
            res = min(res, cal(n, j));
        }
        while(k % j == 0){
            k /= j;
        }
    }
    if(k != 1)res = min(res , cal(n , k));
    return res;
}
