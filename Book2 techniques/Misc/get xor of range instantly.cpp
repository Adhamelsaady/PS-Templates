// XOR of all integers in a range in O(1)
// Problem: Return l XOR (l+1) XOR ... XOR r using the 4-number periodicity of prefix XOR.
// Use: Call `range_xor(l,r)` for an inclusive range.
// Variables: Key variables: l/r=current range endpoints; res=answer. The function peels off odd/even endpoints and uses the parity of the number of pairs.
// Idea: Prefix XOR pattern: xor(0..n) is n,1,n+1,0 for n mod 4 equal to 0,1,2,3 respectively.
// Complexity: Complexity: O(1).

ll range_xor(ll l, ll r) {
    ll res = 0;
    if (l&1) res ^= l++;
    if (!(r&1)) res ^= r--;
    if ((r-l+1)/2&1) res ^= 1;
    return res;
}