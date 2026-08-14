/*
 * Gray Code
 *
 * What this file does:
 * Converts binary integers to Gray code and back.
 *
 * Typical problem to recognize:
 * Gray code is an ordering where consecutive values differ in exactly one bit.
 *
 * Complexity / constraints:
 * Useful for subset enumeration and bitmask transitions.
 *
 * Main variables:
 * x = binary value; g = Gray code.
 *
 * Variable guide for names used in this implementation:
 * g: function/table array.
 * n: main size/index/input value.
 * i: loop index.
 * j: nested loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: g(int n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int g (int n) {
    return n ^ (n >> 1);
//convert from decimal to gray
}

// Function: rev_g(int g).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int rev_g (int g) {
  int n = 0;
//convert from gray to decimal
  for (; g; g >>= 1)
    n ^= g;
  return n;
}
vector<string>GenerateGrayCodeKnownLength(int n){
    vector<string>ans;
    for(int i=0;i<(1<<n);i++){
        bitset<16>b = g(i);
        string temp ;
        for(int j=n-1;j>=0;j--){
            temp+= to_string(b[j]);
        }
        ans.emplace_back(temp);
    }
    return ans;
}
