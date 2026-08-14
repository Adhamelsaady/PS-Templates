auto update = [&] (int u,int v,int t) {
        sz[u] += sz[v] * t;
        dp[u] += (dp[v] + sz[v]) * t;
    };
    function<void(int,int)> dfs = [&](int u,int p)-> void {
        sz[u] = 1;
        for (auto v : adj[u]) {
            if (v != p) {
                dfs(v,u);
                update(u,v,1);
            }
        }
    };
    function<void(int,int)> go = [&](int u,int p)->void {
        res[u] = dp[u];
        for (auto v : adj[u]) {
            if (v != p) {
                // root v
                update(u,v,-1);
                update(v,u,1);

                go(v,u);
                // root u
                update(v,u,-1);
                update(u,v,1);
            }
        }
    };
    dfs(1,0);
    go(1,0);
    for (int i = 1;i <= n;i++) cout << res[i] << " ";