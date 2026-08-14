// Count palindromic paths in a grid
// Problem: Count paths from the top-left to bottom-right of an n*n character grid whose sequence of visited characters is a palindrome. Both walkers move toward the center simultaneously.
// Use: Input n and the grid. The answer is modulo 1e9+7. `dp[i1][i2]` stores ways after k steps with walker A at (i1,j1) and walker B at (i2,j2).
// Variables: Key variables: g=grid; k=steps from both ends; i1/j1=first walker's row/column; i2/j2=second walker's row/column; ways=number of partial palindromic paths; ni1/ni2/nj1/nj2=candidate next positions; dp/ndp=current/next DP layers; ans=final count.
// Idea: Key idea: the two characters chosen at symmetric positions must be equal; when the walkers meet, the whole path is palindromic.
// Complexity: Complexity: O(n^3) time and O(n^2) memory.

#include <bits/stdc++.h>
using namespace std;
static const int MOD = 1000000007;
static int dp[500][500], ndp[500][500];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> g(n);
    for(int i=0;i<n;i++) cin >> g[i];
    if (g[0][0] != g[n-1][n-1]) {
        cout << 0 << "\n";
        return 0;
    }
    dp[0][n-1] = 1;
    for(int k = 0; k < n - 1; k++){
        for(int i=0;i<n;i++) 
            memset(ndp[i], 0, n * sizeof(int));

        int i1_lo = max(0, k-(n-1));
        int i1_hi = min(k, n-1);
        int i2_lo = max(0, (n-1)-k);
        int i2_hi = n-1;

        for(int i1 = i1_lo; i1 <= i1_hi; i1++){
            int j1 = k - i1;
            if (j1 < 0 || j1 >= n) continue;
            for(int i2 = i2_lo; i2 <= i2_hi; i2++){
                int ways = dp[i1][i2];
                if (!ways) continue;
                int j2 = (2*n-2-k) - i2;
                
                int ni1 = i1+1, nj1 = j1;
                int ni2 = i2-1, nj2 = j2;
                if (ni1 < n && ni2 >= 0) {
                    if (g[ni1][nj1] == g[ni2][nj2]) {
                        ndp[ni1][ni2] = (ndp[ni1][ni2] + ways) % MOD;
                    }
                }
                ni1 = i1+1; nj1 = j1;
                ni2 = i2;   nj2 = j2-1;
                if (ni1 < n && nj2 >= 0) {
                    if (g[ni1][nj1] == g[ni2][nj2]) {
                        ndp[ni1][ni2] = (ndp[ni1][ni2] + ways) % MOD;
                    }
                }
                ni1 = i1;   nj1 = j1+1;
                ni2 = i2-1; nj2 = j2;
                if (nj1 < n && ni2 >= 0) {
                    if (g[ni1][nj1] == g[ni2][nj2]) {
                        ndp[ni1][ni2] = (ndp[ni1][ni2] + ways) % MOD;
                    }
                }
                ni1 = i1;   nj1 = j1+1;
                ni2 = i2;   nj2 = j2-1;
                if (nj1 < n && nj2 >= 0) {
                    if (g[ni1][nj1] == g[ni2][nj2]) {
                        ndp[ni1][ni2] = (ndp[ni1][ni2] + ways) % MOD;
                    }
                }
            }
        }
        for(int i=0;i<n;i++)
            memcpy(dp[i], ndp[i], n * sizeof(int));
    }
    long long ans = 0;
    for(int i = 0; i < n; i++){
        ans = (ans + dp[i][i]) % MOD;
    }
    cout << ans << "\n";
}
