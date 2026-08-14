/*
 * nCr with Pascal Triangle
 *
 * What this file does:
 * Precomputes binomial coefficients with Pascal triangle. This works with arbitrary integer arithmetic/modulus because it uses only addition.
 *
 * Typical problem to recognize:
 * Pascal triangle uses C(n,k)=C(n-1,k-1)+C(n-1,k).
 *
 * Complexity / constraints:
 * O(N^2) time and memory.
 *
 * Main variables:
 * C[n][k] = binomial coefficient.
 *
 * Variable guide for names used in this implementation:
 * C: binomial table / constant.
 * n: main size/index/input value.
 * k: count/exponent/selected size.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

const int M = 1001;
int C[M + 1][M + 1];
// Function: PreCalculation().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void PreCalculation() {
    C[0][0] = 1;
    for (int n = 1; n <= M; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k)
            C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }
}
