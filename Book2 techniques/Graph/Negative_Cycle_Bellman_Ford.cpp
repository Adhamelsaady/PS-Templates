#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    Subtask: Detect and Reconstruct Any Negative Cycle

    Pattern:
      - Run Bellman-Ford for n rounds.
      - Initialize every distance to 0 so every connected component is considered.
      - If an edge still relaxes on round n, a negative cycle exists.
      - Follow parent pointers n times to enter the cycle, then reconstruct it.

    Input format:
      n m
      m directed weighted edges: u v w

    Output:
      NO
    or
      YES
      vertices of one negative cycle

    Complexity: O(n * m)
*/

struct Edge {
    int u, v;
    ll w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (auto &e : edges) {
        cin >> e.u >> e.v >> e.w;
        --e.u;
        --e.v;
    }

    // 0 for every vertex = virtual super-source connected to all nodes by 0-cost edges.
    vector<ll> dist(n, 0);
    vector<int> parent(n, -1);

    int changed = -1;

    for (int i = 0; i < n; ++i) {
        changed = -1;

        for (const auto &e : edges) {
            if (dist[e.v] > dist[e.u] + e.w) {
                // Clamp only as a safety guard against very negative accumulated values.
                dist[e.v] = max(-4'000'000'000'000'000'000LL,
                                dist[e.u] + e.w);
                parent[e.v] = e.u;
                changed = e.v;
            }
        }
    }

    if (changed == -1) {
        cout << "NO\n";
        return 0;
    }

    // Move inside the cycle.
    int y = changed;
    for (int i = 0; i < n; ++i)
        y = parent[y];

    // Reconstruct the cycle through parent links.
    vector<int> cycle;
    for (int cur = y;; cur = parent[cur]) {
        cycle.push_back(cur);
        if (cur == y && cycle.size() > 1) break;
    }

    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";
    for (int v : cycle)
        cout << v + 1 << ' ';
    cout << '\n';

    return 0;
}
