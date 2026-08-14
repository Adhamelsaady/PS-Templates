#include <bits/stdc++.h>
using namespace std;

/*
    Subtask: For every node u, find its maximum distance to any other node
             (the eccentricity of u).
    Technique: Tree diameter endpoints.

    Property:
      If A and B are endpoints of a tree diameter, then for every node u:
          eccentricity[u] = max(dist(A,u), dist(B,u)).

    Steps:
      1) BFS/DFS from any node -> farthest node A.
      2) BFS/DFS from A -> distances distA and farthest node B.
      3) BFS/DFS from B -> distances distB.
      4) answer[u] = max(distA[u], distB[u]).

    Complexity: O(N)
*/

int n;
vector<vector<int>> adj;

pair<int, vector<int>> bfs(int source) {
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(source);
    dist[source] = 0;

    int farthest = source;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (dist[u] > dist[farthest]) farthest = u;

        for (int v : adj[u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    return {farthest, dist};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    adj.assign(n, {});

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int A = bfs(0).first;
    auto [B, distA] = bfs(A);
    auto [ignore, distB] = bfs(B);

    for (int u = 0; u < n; ++u)
        cout << max(distA[u], distB[u]) << (u + 1 == n ? '\n' : ' ');
}
