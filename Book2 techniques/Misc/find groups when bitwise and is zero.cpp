// Connected components in a bitmask graph
// Problem: Given n-bit masks, create an implicit graph where two masks are adjacent when their bitwise AND is zero. Count the connected components among the given masks without building all O(m^2) edges.
// Use: Input: n and m, followed by m masks. Call/execute the program as-is. `lim=(1<<n)-1` is the all-ones mask. DFS explores zero-AND-compatible masks through submask transitions.
// Variables: Key variables: n=number of bits; m=number of given masks; a[]=input masks; st[mask]=whether a mask exists; vis[mask]=visited state; lim=all n bits set; res=component count; u=current mask; x=remaining set bits; lb(x)=lowest set bit.
// Idea: Terminology: a bitmask is a set encoded by bits; `u & v == 0` means the two sets are disjoint.
// Complexity: Complexity: depends on the n-bit state space; the implementation uses O(2^n) memory and is intended for small n (and large m).

#include <bits/stdc++.h>
#define pc(c) putchar(c)
#define rep(a,b,c) for (int a = (b) ; a < (c) ; ++a)
#define endl '\n'

using namespace std;
using ll = long long ;
using ai2 = array<int,2> ;

const int maxn = 5e6 + 10 ;

bool st[maxn],vis[maxn] ;
int a[maxn] ;

int lim ;
inline int lb(int x){
    return x & -x ;
};
inline void dfs(int u) {
    if (vis[u]) return  ;
    vis[u] = 1;

    if (st[u]) dfs(u ^ lim) ;
    int x = u ;
    while (x) {        
	dfs(u - lb(x)) ;
        x &= x - 1;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n,m ;
    while(cin >> n >> m) {
        lim = (1 << n) - 1;
        memset(vis,0,lim + 1) ;
        int res = 0 ;
        rep(i,1,m + 1) {
            cin >> a[i],st[a[i]] = 1 ;
            if (!a[i]) res = 1;
        }
        if (!res) {
            rep(i,1,m + 1) {
                if (!vis[a[i]]) {
                    dfs(a[i] ^ lim) ;
                    ++ res ;
                }
            }
        }
        cout << res << endl ;
        rep(i,1,m + 1) st[a[i]] = 0 ;
    }

    return 0;
}