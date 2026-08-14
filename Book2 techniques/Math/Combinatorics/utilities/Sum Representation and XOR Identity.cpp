/*
 * Sum Representation and XOR Identity
 *
 * What this file does:
 * Contains a small arithmetic/XOR identity helper rather than a generic integer-partition algorithm.
 *
 * Typical problem to recognize:
 * The identity (a^x)+(b^x)=a+b-2(a&b) removes the common set bits from both values.
 *
 * Complexity / constraints:
 * Use the actual function behavior, not the filename, when reusing this snippet.
 *
 * Main variables:
 * a,b = input integers; x = a&b, common set bits.
 *
 * Variable guide for names used in this implementation:
 * t: test case or temporary value.
 * a: main input/base/coefficient.
 * x: unknown or current value.
 * sum: running sum.
 * n: main size/index/input value.
 * m: second size or modulus.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;cin>>t;
    while(t--) {
        int a , b;cin>>a>>b;
        int x = a & b;
        cout<<((a ^ x) + (b ^ x))<<'\n';
    }
}
// Function: sum(int n , int m = 0).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int sum(int n , int m = 0){
    if(!m)return (1LL << (n - 1));
    return fast_power(2ll , n - 1 , m);
}
