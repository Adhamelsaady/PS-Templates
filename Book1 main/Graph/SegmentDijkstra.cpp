struct SegmentGraph {
    int n, N;
    vector<vector<array<int, 2>>> g;

    SegmentGraph(int _n) : n(_n) {
        N = 1;
        while (N < n) N <<= 1;
        g.resize(4 * N); // enough for both trees and base nodes
        build_tree_edges();
    }

    // Build segment tree connections
    void build_tree_edges() {
        for (int i = 1; i < N; ++i) {
            g[i].push_back({2 * i, 0});
            g[i].push_back({2 * i + 1, 0});
        }
        for (int i = 1; i < N; ++i) {
            g[2 * i + 2 * N].push_back({i + 2 * N, 0});
            g[2 * i + 1 + 2 * N].push_back({i + 2 * N, 0});
        }
        for (int i = 0; i < n; ++i) {
            g[N + i].push_back({2 * N + N + i, 0});
            g[2 * N + N + i].push_back({N + i, 0});
        }
    }

    // Add normal edge from u to v with weight w
    void add_edge(int u, int v, int w) {
        g[N + u].push_back({N + v, w});
    }

    // Add edges from u to range [l, r]
    void add_edge_to_range(int u, int l, int r, int w) {
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l % 2 == 1) g[N + u].push_back({l++, w});
            if (r % 2 == 0) g[N + u].push_back({r--, w});
        }
    }

    // Add edges from range [l, r] to u
    void add_edge_from_range(int u, int l, int r, int w) {
        for (l += N, r += N; l <= r; l >>= 1, r >>= 1) {
            if (l % 2 == 1) g[2 * N + l++].push_back({N + u, w});
            if (r % 2 == 0) g[2 * N + r--].push_back({N + u, w});
        }
    }

    // Dijkstra from source node s (0-based)
    vector<int> dijkstra(int s) {
        const long long INF = 1e18;
        vector<int> dist(g.size(), INF);
        priority_queue<array<int, 2>, vector<array<int, 2>>, greater<>> pq;

        dist[N + s] = 0;
        pq.push({0, N + s});

        while (!pq.empty()) {
            auto t = pq.top(); pq.pop();
            int d = t[0], u = t[1] ;
            if (d > dist[u]) continue;
            for (auto l : g[u]) {
                int v = l[0], w = l[1] ;
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }

        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = (dist[N + i] >= INF ? -1 : dist[N + i]);
        }
        return res;
    }
};