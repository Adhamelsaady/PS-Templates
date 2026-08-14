/*
 * Modular Inverse with Extended Euclid
 *
 * What this file does:
 * Finds gcd(a,b) and integers x,y such that ax+by=gcd(a,b).
 *
 * Typical problem to recognize:
 * Bézout coefficients are useful because when gcd(a,m)=1, x is a modular inverse of a modulo m.
 *
 * Complexity / constraints:
 * Core building block for modular inverse, CRT, and Diophantine equations.
 *
 * Main variables:
 * a,b = inputs; x,y = Bézout coefficients; g = gcd.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * r: chosen count / remainder / right bound.
 * m: second size or modulus.
 * x: unknown or current value.
 * g: function/table array.
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
// Function: ModInverse(int a,int m).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int ModInverse(int a,int m){
    int x,y;
    int g = gcd_euldien_algo(a,m,x,y);
    return (g==1?(x%m+m)%m:-inf);
//return -inf if there is no mod inverse
}
