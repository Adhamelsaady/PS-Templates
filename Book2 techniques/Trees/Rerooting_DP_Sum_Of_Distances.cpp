#include <bits/stdc++.h>
using namespace std;

/*
    Subtask: For every node u, compute the sum of distances from u to all nodes.
    Technique: Rerooting DP.

    1) Root the tree at 0.
       - sub[u] = subtree size of u
       - ans[0]  = sum of depths from root 0

    2) Reroot across an edge u -> v where v is a child:
         ans[v] = ans[u] - sub[v] + (N - sub[v])
                = ans[u] + N - 2 * sub[v]

       Nodes inside v's subtree become 1 closer; all other nodes become 1 farther.

    Complexity: O(N)
*/

using ll = long long;

int n;
vector<vector<int>> adj;
vector<int> sub;
vector<ll> ans;

void dfs_subtree(int u, int p, int depth) {
    sub[u] = 1;
    ans[0] += depth;

    for (int v : adj[u]) {
        if (v == p) continue;
        dfs_subtree(v, u, depth + 1);
        sub[u] += sub[v];
    }
}

void dfs_reroot(int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;
        ans[v] = ans[u] + n - 2LL * sub[v];
        dfs_reroot(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    adj.assign(n, {});
    sub.assign(n, 0);
    ans.assign(n, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_subtree(0, -1, 0);
    dfs_reroot(0, -1);

    for (int i = 0; i < n; ++i)
        cout << ans[i] << (i + 1 == n ? '\n' : ' ');
}
