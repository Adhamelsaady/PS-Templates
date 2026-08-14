/*
 * Apply Permutation k Times
 *
 * What this file does:
 * Applies a permutation k times without simulating all k operations. The permutation is treated like an object that can be exponentiated with binary lifting.
 *
 * Typical problem to recognize:
 * A permutation power P^k means applying P exactly k times.
 *
 * Complexity / constraints:
 * O(n log k).
 *
 * Main variables:
 * p = permutation; k = number of applications; a/sequence = current values; nxt/power = jump table.
 *
 * Variable guide for names used in this implementation:
 * k: count/exponent/selected size.
 * j: nested loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

vector<int>fp(vector<int>&per , vector<int>&seq , ll k) {
    auto apply = [&](vector<int>&a , vector<int>&b) {
        vector<int>na(a.size());
        for (int j = 0;j < b.size();j++) {
            na[j] = a[b[j] - 1];
        }
        return na;
    };
    auto res = per;
    while (k) {
        if (k & 1) {
            res = apply(res , seq);
        }
        seq = apply(seq , seq);
        k >>= 1;
    }
    return res;
}
