vector <vector<int>> adj;
vector <int> ans , big , sz;
void pre(int u , int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        pre(v , u);
        sz[u] += sz[v];
        if (!big[u] or sz[v] > sz[big[u]]) {
            big[u] = v;
        }
    }
}

void doOperation(int u , bool add) {

}


void collect(int u , int p , int d) {
    doOperation(u , d);
    for (int v : adj[u]) {
        if (v == p) continue;
        collect(v , u , d);
    }
}

void dfs(int u , int p , int keep) {
    for (int v : adj[u]) {
        if (v == p or v == big[u]) continue;
        dfs(v , u , 0);
    }
    // add big
    if (big[u] != 0)
        dfs(big[u] , u , 1);

    doOperation(u , 1);

    for (int v : adj[u]) {
        if (v == p or v == big[u]) continue;
        collect(v , u , 1);
    }

    for (auto [k , id] : queries[u]) {
        ans[id] = freqcnt[k];
    }

    // remove me
    if (!keep) {
        collect(u , p , 0);
    }
}