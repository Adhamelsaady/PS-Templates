#include <bits/stdc++.h>
using namespace std;

/*
    Subtask: Count unordered pairs of tree nodes whose distance is in [K1, K2].
    Technique: Centroid Decomposition + depth-frequency counting.

    At each centroid, process child subtrees one by one.
    totalCnt[d] stores how many already-processed nodes are at depth d
    from the centroid. For the current child, cnt[d] stores its depth counts.
    We count pairs whose path passes through the centroid and whose depth sum
    lies in [K1, K2], then merge the child into totalCnt.

    Complexity: O(N log N)
*/

using ll = long long;

int n, K1, K2;
vector<vector<int>> adj;
vector<int> sub, cnt, totalCnt;
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

void collect_depths(int u, int p, int depth, int& maxDepth) {
    if (depth > K2) return;
    ++cnt[depth];
    maxDepth = max(maxDepth, depth);
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        collect_depths(v, u, depth + 1, maxDepth);
    }
}

void decompose(int entry) {
    int total = calc_size(entry, -1);
    int c = find_centroid(entry, -1, total);
    removed[c] = true;

    // The centroid itself is an already available node at depth 0.
    totalCnt[0] = 1;
    int maxTotalDepth = 0;

    for (int v : adj[c]) {
        if (removed[v]) continue;

        int maxDepth = 0;
        collect_depths(v, c, 1, maxDepth);

        // For each depth d in this child, count previous depths x such that
        // K1 <= d + x <= K2.
        // We sweep d and maintain the needed range sum of totalCnt[x].
        ll window = 0;
        int L = max(0, K1 - 1);
        int R = K2 - 1;
        for (int x = L; x <= R && x <= maxTotalDepth; ++x)
            window += totalCnt[x];

        for (int d = 1; d <= maxDepth; ++d) {
            answer += 1LL * cnt[d] * window;

            // Move from the range needed for depth d to depth d+1:
            // [K1-d, K2-d] -> [K1-d-1, K2-d-1]
            int removeDepth = K2 - d;
            if (0 <= removeDepth && removeDepth <= maxTotalDepth)
                window -= totalCnt[removeDepth];

            int addDepth = K1 - d - 1;
            if (0 <= addDepth && addDepth <= maxTotalDepth)
                window += totalCnt[addDepth];
        }

        for (int d = 1; d <= maxDepth; ++d)
            totalCnt[d] += cnt[d];
        maxTotalDepth = max(maxTotalDepth, maxDepth);

        fill(cnt.begin(), cnt.begin() + maxDepth + 1, 0);
    }

    fill(totalCnt.begin(), totalCnt.begin() + maxTotalDepth + 1, 0);

    for (int v : adj[c]) {
        if (!removed[v]) decompose(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K1 >> K2;
    adj.assign(n, {});
    sub.assign(n, 0);
    cnt.assign(K2 + 1, 0);
    totalCnt.assign(K2 + 1, 0);
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
