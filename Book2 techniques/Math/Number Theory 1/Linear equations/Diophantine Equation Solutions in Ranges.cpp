/*
 * Diophantine Equation Solutions in Ranges
 *
 * What this file does:
 * Solves ax + by = c and counts/finds integer solutions inside requested ranges.
 *
 * Typical problem to recognize:
 * A Diophantine equation requires integer solutions. If gcd(a,b) divides c, all solutions can be generated from one solution by shifting along a direction.
 *
 * Complexity / constraints:
 * O(log max(|a|,|b|)) for the gcd part; range counting is constant time after the base solution.
 *
 * Main variables:
 * a,b,c = equation coefficients; x0,y0 = one base solution; g = gcd(a,b); L/R = lower/upper bounds.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * d: divisor / gcd result / distance depending on function.
 * c: third coefficient/constant.
 * cnt: frequency/count array.
 * x: unknown or current value.
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
    return true;
}
// Function: shift_solution(ll & x, ll & y, ll a, ll b, ll cnt).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void shift_solution(ll & x, ll & y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

// Function: find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
    if (a == 0 && b == 0) return (c == 0) ? (maxx - minx + 1) * (maxy - miny + 1) : 0;
    if (a == 0) {
        if (c % b != 0) return 0;
        ll y0 = c / b;
        if (y0 < miny || y0 > maxy) return 0;
        return (maxx - minx + 1);
    }
    if (b == 0) {
        if (c % a != 0) return 0;
        ll x0 = c / a;
        if (x0 < minx || x0 > maxx) return 0;
        return (maxy - miny + 1);
    }
    ll x, y, g;
    if (!find_any_solution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution(x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    ll lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    ll rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    ll lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy)
        shift_solution(x, y, a, b, sign_a);
    ll rx2 = x;

    if (lx2 > rx2)
        swap(lx2, rx2);
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);

    if (lx > rx)
        return 0;
    return (rx - lx) / abs(b) + 1;
}
