// Sum XOR of every subset
// Problem: Compute the sum of XOR values over all 2^n subsets without enumerating them.
// Use: Call `xorSum(arr,n)`. The snippet expects `mul`, `fast_power`, and `mod` from `cp_template.cpp`. The answer is modulo mod.
// Variables: Key variables: bits=bitwise OR of all elements; ans=final sum; n=number of elements.
// Idea: Formula: sum_XOR(all subsets) = (a1 | a2 | ... | an) * 2^(n-1). Each bit that exists in any element is set in exactly half of all subsets' XORs.
// Complexity: Complexity: O(n log n) with the template exponentiation (or O(n log mod)); O(1) extra space.

int xorSum(vector<int>&arr, int n)
{
    int bits = 0;
    for (int i=0; i < n; ++i)
        bits |= arr[i];
    int ans = mul(bits , fast_power(2ll, n-1,mod),mod);
    return ans;
}