#include <bits/stdc++.h>

using namespace std;
#define int long long

//////////////////////////////////////////////////////////////////////////////

void AC() {
    int n; cin >> n;
    vector <vector<int>> adj(n + 1);
    vector <int> res(n + 1) , dp(n + 1) , sz(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int u , v;  cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    function <void(int , int)> go = [&] (int u , int p) {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v == p) continue;
            go(v , u);
            dp[u] += dp[v] + sz[v];
            sz[u] += sz[v];
        }
    }; go(1 , 0);

    function <void(int , int)> dfs = [&] (int u , int p) {
        res[u] = dp[u];
        for (int v : adj[u]) {
            if (v == p) continue;

            dp[u] -= dp[v] + sz[v];
            sz[u] -= sz[v];

            dp[v] += dp[u] + sz[u];
            sz[v] += sz[u];

            dfs(v , u);

            dp[v] -= dp[u] + sz[u];
            sz[v] -= sz[u];

            dp[u] += dp[v] + sz[v];
            sz[u] += sz[v];
        }
    }; dfs(1 , 0);

    for (int u = 1; u <= n; ++u) cout << res[u] << " ";
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;
    while (t--) AC();
}
