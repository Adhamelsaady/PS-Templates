// k-th smallest element in expected linear time
// Problem: Find the element with zero-based rank k without fully sorting the array.
// Use: Call `findK(v,k)`. Afterward, `v[k]` is the k-th element and elements on either side are partitioned around it (not fully sorted).
// Variables: Key variables: v=array, k=zero-based order statistic.
// Idea: Median is simply k=n/2 for a zero-based index (for an odd-sized array).
// Complexity: Complexity: expected O(n) with `std::nth_element`; worst-case complexity is implementation-dependent and can be higher.

int findK(vector<int> &v, int k){
    nth_element(v.begin(), v.begin() + k, v.end());
    return v[k];
}