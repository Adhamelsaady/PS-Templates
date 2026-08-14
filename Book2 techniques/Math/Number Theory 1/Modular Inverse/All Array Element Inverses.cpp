/*
 * All Array Element Inverses
 *
 * What this file does:
 * Finds x such that a*x = 1 (mod m).
 *
 * Typical problem to recognize:
 * An inverse exists iff gcd(a,m)=1. For prime m, a^(m-2) is the inverse by Fermat’s little theorem.
 *
 * Complexity / constraints:
 * Extended Euclid works for any modulus when gcd is 1.
 *
 * Main variables:
 * a = number to invert; m = modulus; x/inv = inverse.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * r: chosen count / remainder / right bound.
 * m: second size or modulus.
 * n: main size/index/input value.
 * i: loop index.
 * x: unknown or current value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

int extended_euclidean(int a,int b,int &x,int &y)
{
    if(a<0)
    {
        int r= extended_euclidean(-a,b,x,y);
        x*=-1;
        return r;
    }
    if(b<0)
    {
        int r= extended_euclidean(a,-b,x,y);
        y*=-1;
        return r;
    }
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    int sol= extended_euclidean(b,a%b,y,x);
    y-=(a/b)*x;
    return sol;
}
// Function: invs(const std::vector<int> &a, int m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<int> invs(const std::vector<int> &a, int m) {
    int n = (int)a.size();
    if (n == 0) return {};
    std::vector<int> b(n);
    int v = 1;
    for (int i = 0; i != n; ++i) {
        b[i] = v;
        v = static_cast<long long>(v) * a[i] % m;
    }
    int x, y;
    extended_euclidean(v, m, x, y);
    x = (x % m + m) % m;
    for (int i = n - 1; i >= 0; --i) {
        b[i] = static_cast<long long>(x) * b[i] % m;
        x = static_cast<long long>(x) * a[i] % m;
    }
    return b;
}
