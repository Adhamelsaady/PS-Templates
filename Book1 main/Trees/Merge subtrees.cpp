vector<int> adj[N];
int sz[N];
int dp[N][N];

void calc(int u,int p) {
    
    for (auto v : adj[u]) {
        if (v == p) continue;
        calc(v,u);
        
        for (int i = sz[u];i >= 0; i--) {
            for (int j = sz[v]; j >= 0; j--) {
                
            }
        }

        sz[u] += sz[v];
    }
}