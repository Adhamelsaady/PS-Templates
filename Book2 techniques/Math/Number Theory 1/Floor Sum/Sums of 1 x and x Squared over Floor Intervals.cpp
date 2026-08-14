/*
 * Sums of 1 x and x Squared over Floor Intervals
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
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * m: second size or modulus.
 * res: accumulated result.
 * x: unknown or current value.
 * f: function/table array.
 * g: function/table array.
 * c: third coefficient/constant.
 * n: main size/index/input value.
 * d: divisor / gcd result / distance depending on function.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */


const int MOD = 1e9 + 7;

// Function: binpow(ll a, ll b, ll m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll binpow(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

const int inv2 = binpow(2, MOD - 2, MOD);
const int inv6 = binpow(6, MOD - 2, MOD);

// Function: norm(ll x).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll norm(ll x) {
    return ((x % MOD) + MOD) % MOD;
}

// Function: mul(ll a, ll b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll mul(ll a, ll b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

struct dat {
    ll f, g, h;
    dat(ll f = 0, ll g = 0, ll h = 0) : f(f), g(g), h(h) {}
};

// This function calculates:
//   f: sum_{x=0}^{n} floor((a*x + b) / c)
//   g: sum_{x=0}^{n} x * floor((a*x + b) / c)
//   h: sum_{x=0}^{n} [floor((a*x + b) / c)]^2
// Function: query(ll a, ll b, ll c, ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
dat query(ll a, ll b, ll c, ll n) {
    if(a == 0) {
        ll d = b / c;
        ll F = mul(n + 1, d);
        ll G = mul(mul(d, n), (n + 1));
        G = mul(G, inv2);
        ll H = mul(n + 1, d);
        H = mul(H, d);
        return {norm(F), norm(G), norm(H)};
    }
    dat nxt;
    ll f, g, h;
    if(a >= c || b >= c) {
        nxt = query(a % c, b % c, c, n);
        ll term1 = mul(mul(n, n + 1), inv2);
        f = norm(nxt.f + mul(term1, a / c) + mul(n + 1, b / c));
        ll term2 = mul(mul(n, n + 1), mul(2 * n + 1, inv6));
        g = norm(nxt.g + mul(a / c, term2) + mul(mul(b / c, n), (n + 1) * inv2));
        h = norm(
              nxt.h
            + 2 * mul(b / c, nxt.f)
            + 2 * mul(a / c, nxt.g)
            + mul(mul(a / c, a / c), mul(mul(n, n + 1), mul(2 * n + 1, inv6)))
            + mul(mul(b / c, b / c), (n + 1))
            + mul(mul(a / c, b / c), mul(n, n + 1))
        );
        return {f, g, h};
    }
    ll m = (a * n + b) / c;
    nxt = query(c, c - b - 1, a, m - 1);
    f = norm(mul(m, n) - nxt.f);
    ll temp = norm(mul(m, mul(n, n + 1)) - nxt.h - nxt.f);
    g = norm(mul(temp, inv2));
    h = norm(mul(n, mul(m, m + 1)) - 2 * nxt.g - 2 * nxt.f - f);
    return {f, g, h};
}

