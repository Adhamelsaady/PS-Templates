// Original Tree
vector<vector<int>> adj;
vector<bool> deleted;
int cnt = 0;
vector<int> sub_size;

// Centroid Tree
vector<int> par, level;

// Calculate the size of each subtree
void dfs1(int u, int p) {
    sub_size[u] = 1;
    ++cnt;

    for(auto &v : adj[u]) {
        if(v == p || deleted[v]) continue;
        dfs1(v, u);
        sub_size[u] += sub_size[v];
    }
}

int find_centroid(int u, int p) {
    for(auto &v : adj[u]) {
        if(deleted[v] || v == p || sub_size[v] <= cnt / 2) continue;
        return find_centroid(v, u);
    }
    return u;
}

void add_edge_to_centroid_tree(int u, int p) {
    par[u] = p;
    level[u] = level[p] + 1;
}


void decompose(int u, int p) {
    cnt = 0;
    dfs1(u, p);

    int curr_centroid = find_centroid(u, u);

    if(p == -1) p = curr_centroid;
    add_edge_to_centroid_tree(curr_centroid, p);

    // solve

    deleted[curr_centroid] = 1;
    for(auto &v : adj[curr_centroid]) {
        if(deleted[v]) continue;
        decompose(v, curr_centroid);
    }
}

void init(int n) {

    cnt = 0;
    adj.assign(n + 1, {});
    deleted.assign(n + 1, 0);
    sub_size.assign(n + 1, 0);

    par.assign(n + 1, 0);
    level.assign(n + 1, 0);
}
