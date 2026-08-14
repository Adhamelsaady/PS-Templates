// K shortest path distances
// Problem: Find the first k shortest walk distances from vertex 1 to vertex n in a directed weighted graph with non-negative edge weights. A vertex may be popped from the priority queue up to k times.
// Use: The snippet expects `N` and `khaled` from the common template. Input n,m,k then m edges (u,v,w). It prints the k distances found.
// Variables: Key variables: adj[u]=outgoing edges; n,m,k=vertices/edges/number of paths; q=min-priority queue of {distance,vertex}; cnt[v]=how many times v has been expanded; ans=distances reaching destination; start/end=source/destination.
// Idea: Important: this is for k shortest walks, not necessarily k vertex-disjoint paths. Non-negative weights are required for the Dijkstra-like ordering.
// Complexity: Complexity: roughly O(k*m log(km)) in the worst case.

vector<pair<int,int>> adj[N];
int n , m, k;
signed main() {
    khaled
    cin >> n >> m >> k;
    for(int i = 0; i < m; ++i){
        int u , v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v , w);
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
    vector<int> cnt(n) , ans;
    int start = 0 , end = n - 1;
    q.push({0 , start});
    while(q.size() && cnt[end] < k){
        auto [d , u] = q.top(); q.pop();
        cnt[u]++;
        if(u == end) ans.emplace_back(d);
        if(cnt[u] <= k){
            for(auto &[v,  w] : adj[u]) {
                if (cnt[v] < k)
                    q.push({(w + d), v});
            }
        }
    }
    sort(ans.begin() , ans.end());
    for(auto &w : ans) cout << w << " ";
}
