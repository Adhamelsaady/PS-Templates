// Minimum patches to cover every sum from 1 to n
// Problem: Given a sorted positive array, add the fewest numbers so every integer in [1,n] becomes representable as a subset sum.
// Use: Call `minPatches(nums,n)`. `nums` must be sorted in nondecreasing order and contain positive values.
// Variables: Key variables: miss=smallest value not currently representable; i=current input index; result=number of inserted values.
// Idea: Greedy invariant: if [1,miss-1] is covered and nums[i] <= miss, coverage extends to miss+nums[i]-1; otherwise the optimal patch is exactly miss, doubling coverage to 2*miss-1.
// Complexity: Complexity: O(nums.size()) time and O(1) extra space.

ll minPatches(vector<ll>& nums, ll n) {
        long long miss = 1;
        ll result = 0;
        size_t i = 0;

        while (miss <= n) {
            if (i < nums.size() && nums[i] <= miss) {
                miss += nums[i];
                i++;
            } else {
                miss += miss;
                result++;
            }
        }

        return result;
    }