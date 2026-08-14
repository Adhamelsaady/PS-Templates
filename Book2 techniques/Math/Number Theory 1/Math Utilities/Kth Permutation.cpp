/*
 * Kth Permutation
 *
 * What this file does:
 * Finds the kth permutation or its lexicographic index.
 *
 * Typical problem to recognize:
 * Lexicographic order is dictionary order over sequences.
 *
 * Complexity / constraints:
 * Ranks are usually 0-based or 1-based; check the function contract.
 *
 * Main variables:
 * k/nth = requested rank; n = length; fact = factorials; available = unused values.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * nth: requested 1-based rank.
 * i: loop index.
 * p: prime/modulus/parameter depending on function.
 * n: main size/index/input value.
 * j: nested loop index.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// send permutation in zero base , kth start from 0
// build factorials first
const int N = 21;
ll Fact[N];
// Function: nthPerm(ll len, ll nth).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
vector<ll> nthPerm(ll len, ll nth) {
	vector<ll> identity(len), perm(len);
	for (int i = 0;i < len;i++) identity[i] = i;

	for (int i = len - 1; i >= 0; --i) {
		ll p = nth / Fact[i];
		perm[len - 1 - i] = identity[p];
		identity.erase(identity.begin() + p);
		nth %= Fact[i];
	}
	return perm;
}
// Function: PermToIndex(vector<int> perm).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll PermToIndex(vector<int> perm) {
	ll idx = 0;
	int n = perm.size();
	for (int i = 0; i < n; ++i) {
		// Remove first, and Renumber the remaining elements to remove gaps
		idx += Fact[n-i-1] * perm[i];
		for(int j = i+1; j < n; j++)
			perm[j] -= perm[j] > perm[i];
	}
	return idx;
}
