/*
 * Diophantine Equation Solutions in x y Ranges
 *
 * What this file does:
 * Finds or counts integer solutions of ax + by = c while x and y must stay inside given intervals.
 *
 * Typical problem to recognize:
 * All integer solutions of ax+by=c form x=x0+(b/g)t, y=y0-(a/g)t. The bounds become an interval for t.
 *
 * Complexity / constraints:
 * O(log max(|a|,|b|)) for Extended Euclid plus O(1) range arithmetic.
 *
 * Main variables:
 * a,b,c = coefficients; x0,y0 = one solution; g = gcd(a,b); lx,rx,ly,ry = bounds.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * r: chosen count / remainder / right bound.
 * c: third coefficient/constant.
 * q: quotient or second input.
 * d: divisor / gcd result / distance depending on function.
 * L: left bound / LCM depending on function.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

ll gcd_euldien_algo(ll a,ll b,ll &x,ll &y)
{
    if(a<0)
    {
        ll r= gcd_euldien_algo(-a,b,x,y);
        x*=-1;
        return r;
    }
    if(b<0)
    {
        ll r= gcd_euldien_algo(a,-b,x,y);
        y*=-1;
        return r;
    }
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    ll sol= gcd_euldien_algo(b,a%b,y,x);
    y-=(a/b)*x;
    return sol;
}
// Function: find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd_euldien_algo(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    g = abs(g);
    return true;                             // a*x + b*y = c     //__gcd(a,b)|c
}
// x0 contain the x cofficent
// y0 contain the y cofficent
// g  contain the gcd


// to get more solutions we can x0 = x0 +k*b/g
//                              y0 = y0 -k*a/g

// Function: floorDiv(ll a, ll b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll floorDiv(ll a, ll b) {
    assert(b != 0);
    ll q = a / b;
    if ((a ^ b) < 0 && a % b) --q;
    return q;
}

// Function: ceilDiv(ll a, ll b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll ceilDiv(ll a, ll b) {
    assert(b != 0);
    ll q = a / b;
    if ((a ^ b) >= 0 && a % b) ++q;
    return q;
}
// Function: find_all(ll a , ll b , ll c , ll x1 , ll x2 , ll y1 , ll y2).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll find_all(ll a , ll b , ll c , ll x1 , ll x2 , ll y1 , ll y2) {
    if (a == 0 && b == 0) {
        return (c == 0)
             ? (x2 - x1 + 1) * (y2 - y1 + 1)
             : 0;
    }
    if (a == 0) {
        if (c % b != 0) return 0;
        ll y0 = c / b;
        if (y0 < y1 || y0 > y2) return 0;
        return (x2 - x1 + 1);
    }
    if (b == 0) {
        if (c % a != 0) return 0;
        ll x0 = c / a;
        if (x0 < x1 || x0 > x2) return 0;
        return (y2 - y1 + 1);
    }

    ll X = -1 , Y = -1 , g = -1;
    if (!find_any_solution(a , b , c , X , Y , g)) {
        return 0;
    }else {
        auto get = [&](ll s, ll lo, ll hi, ll delta, int sign) {
            ll d = delta * sign;
            ll L, R;
            if (d > 0) {
                L = ceilDiv(lo - s, d);
                R = floorDiv(hi - s, d);
            } else {
                L = ceilDiv(hi - s, d);
                R = floorDiv(lo - s, d);
            }
            return make_pair(L, R);
        };

        auto p1 = get(X , x1 , x2 , b / g , 1);
        auto p2 = get(Y , y1 , y2 , a / g , -1);
        auto ans = pair<ll , ll>{max(p1.first , p2.first) , min(p2.second , p1.second)};
        return max(0LL , ans.second - ans.first + 1);
    }
}
