#include <bits/stdc++.h>
using namespace std;

/*
    Subtask: Count unordered pairs of tree nodes whose distance is exactly K.
    Technique: Centroid Decomposition.

    Idea at each centroid:
      - cnt[d] = number of nodes at depth d from the centroid among
        previously processed child subtrees (centroid itself starts at depth 0).
      - For every node at depth d in the current child subtree, add cnt[K-d].
      - Then insert this child's depths into cnt.
      - Recurse on the components after removing the centroid.

    Complexity: O(N log N)
*/

using ll = long long;

int n, K;
vector<vector<int>> adj;
vector<int> sub, cnt;
vector<char> removed;
ll answer = 0;

int calc_size(int u, int p) {
    sub[u] = 1;
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        sub[u] += calc_size(v, u);
    }
    return sub[u];
}

int find_centroid(int u, int p, int total) {
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (sub[v] * 2 > total)
            return find_centroid(v, u, total);
    }
    return u;
}

void count_paths(int u, int p, int depth) {
    if (depth > K) return;
    answer += cnt[K - depth];
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        count_paths(v, u, depth + 1);
    }
}

void add_depths(int u, int p, int depth, vector<int>& touched) {
    if (depth > K) return;
    if (cnt[depth] == 0) touched.push_back(depth);
    ++cnt[depth];
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        add_depths(v, u, depth + 1, touched);
    }
}

void decompose(int entry) {
    int total = calc_size(entry, -1);
    int c = find_centroid(entry, -1, total);

    vector<int> touched;
    cnt[0] = 1;
    touched.push_back(0);

    for (int v : adj[c]) {
        if (removed[v]) continue;
        count_paths(v, c, 1);
        add_depths(v, c, 1, touched);
    }

    for (int d : touched) cnt[d] = 0;

    removed[c] = true;
    for (int v : adj[c]) {
        if (!removed[v]) decompose(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K;
    adj.assign(n, {});
    sub.assign(n, 0);
    cnt.assign(K + 1, 0);
    removed.assign(n, false);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    decompose(0);
    cout << answer << '\n';
}
