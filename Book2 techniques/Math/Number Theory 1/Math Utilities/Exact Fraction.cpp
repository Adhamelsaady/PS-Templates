/*
 * Exact Fraction
 *
 * What this file does:
 * Stores rational numbers exactly as numerator/denominator and reduces them by gcd.
 *
 * Typical problem to recognize:
 * A rational number is an exact ratio of two integers, unlike floating point which may have rounding error.
 *
 * Complexity / constraints:
 * Useful for geometry and exact comparisons.
 *
 * Main variables:
 * num = numerator; den = denominator.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * n: main size/index/input value.
 * d: divisor / gcd result / distance depending on function.
 * g: function/table array.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: gcd(long long a, long long b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
long long gcd (long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
struct frac{
    // fraction n / d
    long long n ,d;
    // constructor
    frac(){n = 0; d = 1;}
    frac(ll n , ll d): n(n) , d(d){simplify();};
    bool operator < (const frac &other) const{
        return n * other.d < d * other.n;
    }
    frac operator + (const frac &f) const{
        frac ans {n * f.d + f.n * d , d * f.d};
        ans.simplify();
        return ans;
    }
    frac operator - (const frac &f) const{
        frac ans {n * f.d - f.n * d , d * f.d};
        ans.simplify();
        return ans;
    }
    void Abs(){n = abs(n); d = abs(d);}
    // Function: simplify().
    // Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
    void simplify(){
        long long g = gcd(abs(n) , abs(d));
        n /= g; d /= g;
    }
};
