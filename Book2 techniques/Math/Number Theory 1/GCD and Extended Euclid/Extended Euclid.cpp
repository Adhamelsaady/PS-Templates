/*
 * Extended Euclid
 *
 * What this file does:
 * Computes the greatest common divisor, including variants for negatives or using only binary operations.
 *
 * Typical problem to recognize:
 * gcd(a,b) is the largest positive integer dividing both numbers.
 *
 * Complexity / constraints:
 * Binary GCD uses shifts/subtraction; Extended Euclid also gives coefficients.
 *
 * Main variables:
 * a,b = input integers; x,y = Bézout coefficients in extended Euclid; g = gcd.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * r: chosen count / remainder / right bound.
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
