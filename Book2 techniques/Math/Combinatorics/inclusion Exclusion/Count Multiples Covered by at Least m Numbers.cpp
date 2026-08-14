/*
 * Count Multiples Covered by at Least m Numbers
 *
 * What this file does:
 * Counts elements satisfying several overlapping conditions by adding single sets, subtracting pair intersections, and alternating signs.
 *
 * Typical problem to recognize:
 * Inclusion-exclusion corrects overcounting caused by overlaps.
 *
 * Complexity / constraints:
 * For n conditions, brute-force over subsets is O(2^n), so it is intended for small n.
 *
 * Main variables:
 * n = number of conditions; m = required number of selected conditions; y = upper bound; a = condition values; mask = chosen subset.
 *
 * Variable guide for names used in this implementation:
 * C: binomial table / constant.
 * i: loop index.
 * j: nested loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

const int C = 21;
ull binom[C][C];
// Function: init().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void init() {
    for(int i = 0; i < C; i++)
        binom[i][0] = binom[i][i] = 1;
    for(int i = 2; i < C; i++)
        for(int j = 1; j < i; j++)
            binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];

}
// calc(elements count , subset size , upper bound , elements)
// call init first
// Function: calc(ull n , ull m , ull y , vector<ull> &a).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll calc(ull n , ull m , ull y , vector<ull> &a) {
    ull ans = 0;
    for(ull msk = 0; msk < (1 << n); msk++) {
        if (popcount(msk) < m) continue;
        ull L = 1;
        for(int i = 0; i < n; i++) {
            if (~msk >> i & 1) continue;
            ull g = gcd(L, a[i]);
            if ((__int128)(L) * a[i] / g > y) L = y + 1;
            else L *= a[i] / g;
        }
        if (popcount(msk) % 2 == m % 2)
            ans += (y / L) * binom[popcount(msk)][m];
        else
            ans -= (y / L) * binom[popcount(msk)][m];
    }

    return ans;
}
