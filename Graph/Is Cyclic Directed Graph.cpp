vector<vector<int>> adj;
vector<int> vis;
bool IsCyclic (int u) {
    vis[u] = 1;
    for(auto v : adj[u]){
        if(!vis[v]) {
            if(!IsCyclic(v))
                return true;
        }
        else if(vis[v] == 1)
            return true;
    }
    vis[u] = 2;
    return false;
}
