// Maximize the minimum distance under cyclic rotations
// Problem: Sort both sequences, cyclically rotate the second sequence, and maximize the minimum paired absolute difference over all rotations.
// Use: Input t test cases. For each case input n and two sequences. The program prints the best minimum distance.
// Variables: Key variables: a,b=sorted sequences; res=best minimum distance over rotations; temp=minimum paired distance for the current rotation; n=number of rotations/positions.
// Idea: Use this when the allowed rearrangement of one sequence is restricted to cyclic shifts after sorting.
// Complexity: Complexity: O(n^2 + n log n) per test case.

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    int t;cin>>t;
    while(t--) {
        int n;cin>>n;
        deque<int>a(n) , b(n);
        for(auto &val:a)cin>>val;
        for(auto &val:b)cin>>val;
        sort(a.begin() , a.end());
        sort(b.begin() , b.end());
        int res = 0;
        while(n--) {
            int temp = 2e9;
            for(int i = 0;i < a.size();++i) {
                temp = min(temp , abs(a[i] - b[i]));
            }
            res = max(res , temp);
            b.push_front(b.back());
            b.pop_back();
        }
        cout<<res<<'\n';
    }
}