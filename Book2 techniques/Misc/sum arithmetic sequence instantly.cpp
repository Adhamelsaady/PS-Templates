// Arithmetic progression sum
// Problem: Return the sum of `len` terms starting at s with common difference inc: s + (s+inc) + ... .
// Use: Call `sum(s,inc,len)`. Example: `sum(3,2,4)=24`.
// Variables: Key variables: s=first term; inc=common difference; len=number of terms.
// Idea: Formula: len * (2*s + (len-1)*inc) / 2.
// Complexity: Complexity: O(1).

ll sum(ll s, ll inc, ll len) {
        return (len * (2 * s + (len - 1) * inc)) / 2;
    }