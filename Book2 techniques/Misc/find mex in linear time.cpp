// MEX in linear time
// Problem: Find the Minimum EXcluded non-negative integer: the smallest x >= 0 that does not occur in the array.
// Use: Call `mex(a)`. The input is copied, so the original array is not modified.
// Variables: Key variables: a=input array; b=working copy; n=array length; i=current index. The swap loop tries to place value x at position x.
// Idea: Example: MEX([0,1,3]) = 2. Values outside [0,n-1] cannot be the MEX of an n-element array.
// Complexity: Complexity: O(n) time (amortized) and O(n) extra memory.

ll mex(const vector<ll>&a) {
    vector<ll>b = a;
    int n = a.size();
    for(int i = 0;i < n;i++) {
        while(b[i] >= 0 && b[i] < n && b[b[i]] != b[i]) {
            swap(b[i] , b[b[i]]);
        }
    }
    for(int i = 0;i < n;i++) {
        if(b[i] != i)return i;
    }
    return n;
}