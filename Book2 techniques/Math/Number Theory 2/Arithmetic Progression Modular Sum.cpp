/*
 * Arithmetic Progression Modular Sum
 *
 * What this file does:
 * Computes sums over a sequence a*i+b, sometimes after division/mod/floor.
 *
 * Typical problem to recognize:
 * An arithmetic progression changes by a constant difference each step.
 *
 * Complexity / constraints:
 * These templates are often paired with floor-sum transformations.
 *
 * Main variables:
 * a,b = progression coefficients; n = number of terms; mod = modulus; ans = sum.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * n: main size/index/input value.
 * a: main input/base/coefficient.
 * d: divisor / gcd result / distance depending on function.
 * m: second size or modulus.
 * res: accumulated result.
 * t: test case or temporary value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;
/*
Sums of arithmetic progressions.
mod_sum(n, a, d, m) = \sum_{i = 0}^{n - 1}{(a + d * i) % m}.
floor_sum(n, a, d, m) = \sum_{i = 0}^{n - 1}{(a + d * i) / m}.
log(m), with a large constant.
*/
// Function: sumsq(long long n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
long long sumsq(long long n) {
    return n / 2 * ((n - 1) | 1);
}
// Function: floor_sum(long long a, long long d, long long m, long long n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
long long floor_sum(long long a, long long d, long long m, long long n) {
    long long res = d / m * sumsq(n) + a / m * n;
    d %= m; a %= m;
    if (!d) return res;
    long long to = (n * d + a) / m;
    return res + (n - 1) * to - floor_sum(m - 1 - a, m, d, to);
}
// Function: mod_sum(long long a, long long d, long long m, long long n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
long long mod_sum(long long a, long long d, long long m, long long n) {
    a = ((a % m) + m) % m;
    d = ((d % m) + m) % m;
    return n * a + d * sumsq(n) - m * floor_sum(a, d, m, n);
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
    	int n, m, a, b; cin >> n >> m >> a >> b;
    	cout << floor_sum(b, a, m, n) << '\n';
    }
    return 0;
}
