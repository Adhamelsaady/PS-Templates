/*
 * Linear Congruence Equation
 *
 * What this file does:
 * Solves ax = b (mod m).
 *
 * Typical problem to recognize:
 * A linear congruence is an equation where two integers are considered equal modulo m.
 *
 * Complexity / constraints:
 * A solution exists iff gcd(a,m) divides b.
 *
 * Main variables:
 * a,b,m = congruence coefficients/modulus; x = solution.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * r: chosen count / remainder / right bound.
 * c: third coefficient/constant.
 * m: second size or modulus.
 * x: unknown or current value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

int gcd_euldien_algo(int a,int b,int &x,int &y)
{
    if(a<0)
    {
        int r= gcd_euldien_algo(-a,b,x,y);
        x*=-1;
        return r;
    }
    if(b<0)
    {
        int r= gcd_euldien_algo(a,-b,x,y);
        y*=-1;
        return r;
    }
    if(b==0)
    {
        x=1,y=0;
        return a;
    }
    int sol= gcd_euldien_algo(b,a%b,y,x);
    y-=(a/b)*x;
    return sol;
}
// Function: find_any_solution(int a, int b, int c, int &x0, int &y0, int &g).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
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
// Function: LinearCongruenceEquation(int a,int b,int m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int LinearCongruenceEquation(int a,int b,int m){
    int x,y,g;
    if(find_any_solution(a,m,b,x,y,g)){
        return (x%m+m)%m;
    }
    return -inf;
}
// solve a * x [=] b % n
// [=]-----> congruence
// to find the value of x if exist you solve     a * x + n * k = b by linear Diophantian equation
