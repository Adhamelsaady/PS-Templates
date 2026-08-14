struct LCA {
    vector<vector<int>> ancestor;
    vector<int> level;
    int LG;
 
    LCA(vector<vector<int>> &adj) {
        int n = (int) adj.size();
        LG = __lg(n) + 1;
        ancestor.assign(LG, vector<int>(n));
        level.assign(n, {});
        build(1, 0, adj);
 
        for (int i = 1; i < LG; ++i) {
            for (int u = 1; u < n; ++u) {
                ancestor[i][u] = ancestor[i - 1][ancestor[i - 1][u]];
            }
        }
    }
 
    void build(int u, int p, vector<vector<int>> &adj) {
        for (auto v: adj[u]) {
            if (v == p)continue;
 
            level[v] = level[u] + 1;
            ancestor[0][v] = u;
            build(v, u, adj);
        }
    }
 
    int KthAnc(int u, int k) {
        for (int i = 0; k; ++i, k >>= 1) {
            if (k & 1)
                u = ancestor[i][u];
        }
        return u;
    }
 
    int getLCA(int u, int v) {
        if (level[u] > level[v])swap(u, v);
        int k = level[v] - level[u];
        v = KthAnc(v, k);
        if (v == u)return v;
 
        for (int i = LG - 1; ~i; --i) {
            if (ancestor[i][v] != ancestor[i][u]) {
                v = ancestor[i][v];
                u = ancestor[i][u];
            }
        }
        return ancestor[0][u];
    }
 
    int getDist(int u, int v) {
        int lca = getLCA(u, v);
 
        return level[u] + level[v] - 2 * level[lca];
    }
};