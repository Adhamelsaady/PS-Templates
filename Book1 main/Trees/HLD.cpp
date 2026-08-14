
vector<vector<int>> adj;
vector<int> par, depth, in, sz, big, head, vals;
int timer = 1;

void dfs(int u, int p, int d = 0) {
    par[u] = p, depth[u] = d, sz[u] = 1;

    int mx = 0;
    for (int &v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
        if (sz[v] > mx) big[u] = v, mx = sz[v];
        sz[u] += sz[v];
    }
}

void flatten(int u, int hd) {
    head[u] = hd , in[u] = timer++;
    if (big[u])
        flatten(big[u], hd);

    for (int &v : adj[u])
        if (v != par[u] && v != big[u])
            flatten(v, v);
}

void init(int n) {
    timer = 1;
    adj.assign(n + 1, {});
    par.assign(n + 1, {});
    depth.assign(n + 1, {});
    in.assign(n + 1, {});
    sz.assign(n + 1, {});
    big.assign(n + 1, {});
    head.assign(n + 1, {});
    vals.assign(n + 1, {});
}

void HLD() {
    dfs(1 , 1 , 0);
    flatten(1 , 1);
}

int query(int l, int r) {
    return 0;
}

int getPath(int u, int v) {
    int a = head[u], b = head[v];

    int res = 0;
    while (a != b) {
        if (depth[a] < depth[b]) swap(a, b), swap(u, v);
        res = res + query(in[a], in[u]);
        u = par[a], a = head[u];
    }

    if (in[u] > in[v]) swap(u, v);
    res = res + query(in[u], in[v]);
    return res;
}

vector <pair<int,int>>  getRanges(int u, int v) {
    vector <pair<int,int>> ret;
    int a = head[u], b = head[v];

    int res = 0;
    while (a != b) {
        if (depth[a] < depth[b]) swap(a, b), swap(u, v);
        ret.emplace_back(in[a], in[u]);
        u = par[a], a = head[u];
    }

    if (in[u] > in[v]) swap(u, v);
    ret.emplace_back(in[u], in[v]);
    return ret;
}

array<vector<pair<int , int>>, 2> getOrderedRanges(int u, int v) {
    array<vector<pair<int, int>> , 2> ret;
    while (head[u] != head[v]) {
        if (depth[head[u]] >= depth[head[v]]) {
            ret[0].emplace_back(in[head[u]], in[u]);
            u = par[head[u]];
        } else {
            ret[1].emplace_back(in[head[v]] , in[v]);
            v = par[head[v]];
        }
    }
    if (in[u] <= in[v])
        ret[1].emplace_back(in[u], in[v]);
    else
        ret[0].emplace_back(in[v], in[u]);
    reverse(ret[1].begin() , ret[1].end());
    return ret;
}

int getSubtree(int u) {
    return query(in[u], in[u] + sz[u] - 1);
}

void updateNode(int u, int value) {
    // update pos[u] in the structure
}