/*
 * Floor Sum
 *
 * What this file does:
 * Computes sums involving floor((a*i+b)/m) without iterating over every i.
 *
 * Typical problem to recognize:
 * floor(x) is the greatest integer <= x. Floor-sum algorithms repeatedly swap numerator and modulus to shrink the problem.
 *
 * Complexity / constraints:
 * Usually O(log m) for the standard floor sum.
 *
 * Main variables:
 * n = number of terms; m = denominator/modulus; a,b = linear expression coefficients; ans = sum.
 *
 * Variable guide for names used in this implementation:
 * x: unknown or current value.
 * y: unknown or current value.
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * c: third coefficient/constant.
 * n: main size/index/input value.
 * res: accumulated result.
 * m: second size or modulus.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: floor_div(ll x, ll y).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
static inline ll floor_div(ll x, ll y) {
    if (y <= 0) throw;
    if (x >= 0) return x / y;
    // for negative x: floor(x/y) = - ((-x + y - 1) / y)
    return - ( ( -x + y - 1 ) / y );
}

// sum_{i=0..n-1} floor((a*i + b) / c)
// Function: floorSum(ll a, ll b, ll c, ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll floorSum(ll a, ll b, ll c, ll n) {
    if (n <= 0) return 0;
    ll qa = floor_div(a, c);
    ll qb = floor_div(b, c);
    ll res = qa * (n * (n - 1) / 2) + qb * n;

    a -= qa * c;
    b -= qb * c;

    if (a < 0) a += c;
    if (b < 0) b += c;

    ll m = (a * n + b) / c;
    if (m == 0) return res;

    ll new_b = (a * n + b) % c;
    return res + floorSum(c, new_b, a, m);
}
