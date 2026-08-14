// Count subarrays with required minimum and maximum
// Problem: Count subarrays whose values stay inside [mn,mx] and contain both mn and mx.
// Use: Call `CountSubArraysWithKnownMxAndMn(v,mn,mx)`. This assumes `mn <= mx`.
// Variables: Key variables: v=input array; mn/mx=required minimum/maximum; l=left boundary after the last invalid value; maxi=last position of mx; mini=last position of mn; r=current right endpoint; ans=answer.
// Idea: At right endpoint r, every valid left endpoint is at most min(last_mx,last_mn) and strictly after the last invalid element.
// Complexity: Complexity: O(n) time and O(1) extra space.

int CountSubArraysWithKnownMxAndMn(vector<int>&v , int mn,int mx){
    int ans=0;
    int maxi=-1, mini=-1;
    int s=(int)v.size();
    for(int r=0, l=0; r<s; r++){
        int x=v[r];
        if (x<mn ||x>mx){
            l=r+1;
            continue;
        }
        if (x==mx) maxi=r;
        if (x==mn) mini=r;
        ans+=max((min(maxi, mini)-l+1),0ll);
    }
    return ans;
}