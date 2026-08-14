struct Bridges {
    int n, m , timer = 1, sz = 0;
    vector<vector<pair<int , int>>> adj;
    vector <vector<int>> tree, BCC;
    vector<int> in, low, st, root , isBridge;
    vector<array<int, 2>> brdgs;

    Bridges(int n , int m): n(n) , m(m) {};

    void build(vector<vector<pair<int , int>>>& _adj) {
        adj = _adj;
        in.assign(n + 1, 0);
        low.assign(n + 1, 0);
        root.assign(n + 1, 0);
        isBridge.assign (m + 1 , 0);
        for (int u = 1; u <= n; ++u)
            if (!in[u]) dfs(u);

        sz = BCC.size();
        tree.assign(n + 1, {});
        for (int u = 1; u <= n; u++)
            for (auto &[v , _]: adj[u])
                if (root[u] != root[v])
                    tree[root[u]].push_back(root[v]);
    }

    void dfs(int u, int p = 0) {
        st.push_back(u);
        in[u] = low[u] = timer++;
        bool pFound = 0;
        for (auto &[v , idx] : adj[u]) {
            if(!pFound && v == p) {
                pFound = 1;
                continue;
            }
            if(!in[v]) dfs(v, u);
            low[u] = min(low[u], low[v]);
            if(low[v] > in[u]) brdgs.push_back({u, v});
        }

        if (low[u] == in[u]) {
            vector<int> c;
            while (st.back() != u)
                c.push_back(st.back()), st.pop_back();
            c.push_back(st.back()), st.pop_back();
            for (int v: c) root[v] = c.front();
            BCC.push_back(c);
        }
    }
};
