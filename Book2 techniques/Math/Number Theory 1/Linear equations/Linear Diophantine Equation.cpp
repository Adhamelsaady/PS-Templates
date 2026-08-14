/*
 * Linear Diophantine Equation
 *
 * What this file does:
 * Solves integer equations such as ax+by=c, including bounded/nonnegative variants.
 *
 * Typical problem to recognize:
 * A Diophantine equation requires integer solutions. ax+by=c has a solution iff gcd(a,b) divides c.
 *
 * Complexity / constraints:
 * Use floor/ceil division carefully for negative bounds.
 *
 * Main variables:
 * a,b,c = equation coefficients; x,y = unknown integer solution; L/R = bounds when present.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * d: divisor / gcd result / distance depending on function.
 * c: third coefficient/constant.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: gcd(ll a, ll b, ll& x, ll& y).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

// Function: find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;  // a*x + b*y = c     //__gcd(a,b)|c
}
// x0 contain the x cofficent
// y0 contain the y cofficent
// g  contain the gcd


// to get more solutions we can x0 = x0 +k*b/g
//                              y0 = y0 -k*a/g
