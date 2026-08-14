/**
 * Quadratic equation solver for a*x^2 + b*x + c = 0.
 *
 * complex<double> is used so both real and complex roots are supported. The
 * discriminant is allowed to be negative. Before using this as a generic helper,
 * handle the degenerate case a==0 separately.
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long

#define double long double  // ************
// Solve a*x^2+b*x+c=0 using the quadratic formula; complex roots are supported.
const double EPS = 1e-9;

pair <complex<double>, complex<double>> solveQuadratic(double a, double b, double c) {
    complex<double> discriminant = b * b - 4.0 * a * c;
    complex<double> sqrt_discriminant = sqrt(discriminant);
    complex<double> root1 = (-b + sqrt_discriminant) / (2.0 * a);
    complex<double> root2 = (-b - sqrt_discriminant) / (2.0 * a);
    return {root1, root2};
}