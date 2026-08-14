/* problem statement text */
/*
CSES - Flight Routes

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to find the kkk shortest flight routes from Syrjälä to Metsälä. A route can visit the same city several times.
Note that there can be several routes with the same price and each of them should be considered (see the example).
Input
The first input line has three integers nnn, mmm, and kkk: the number of cities, the number of flights, and the parameter kkk. The cities are numbered 1,2,…,n1,2,\ldots,n1,2,…,n. City 1 is Syrjälä, and city nnn is Metsälä.
After this, the input has mmm lines describing the flights. Each line has three integers aaa, bbb, and ccc: a flight begins at city aaa, ends at city bbb, and its price is ccc. All flights are one-way flights.
You may assume that there are at least kkk distinct routes from Syrjälä to Metsälä.
Output
Print kkk integers: the prices of the kkk cheapest routes sorted according to their prices.
Constraints

2≤n≤1052 \le n \le 10^52≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤c≤1091 \le c \le 10^91≤c≤109
1≤k≤101 \le k \le 101≤k≤10

Example
Input:
4 6 3
1 2 1
1 3 3
2 3 2
2 4 6
3 2 8
3 4 1

Output:
4 4 7

Explanation: The cheapest routes are 1→3→41 \rightarrow 3 \rightarrow 41→3→4 (price 444), 1→2→3→41 \rightarrow 2 \rightarrow 3 \rightarrow 41→2→3→4 (price 444) and 1→2→41 \rightarrow 2 \rightarrow 41→2→4 (price 777).
*/

using namespace std;
#define int long long

//////////////////////////////////////////////////////////////////////////////
const int mod = 1e9 + 7;
void AC() {
    int n , m , k; cin >> n >> m >> k;
    vector <vector<pair<int , int >>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[--u].emplace_back(--v , w);
    }
    vector <vector<int>> dist(n);
    priority_queue <pair<int , int>> pq;
    pq.emplace(0 , 0);
    while (!pq.empty()) {
        auto [cost , u] = pq.top();
        pq.pop();
        if (size(dist[u]) == k) continue;
        cost *= -1;
        dist[u].emplace_back(cost);
        for (auto &[v , w] : adj[u]) {
            if (dist[v].size() < k) {
                pq.emplace(-(w + cost), v);
            }
        }
    }
    sort(begin(dist.back()) , end(dist.back()));
    for (auto x : dist.back()) cout << x << ' ';
}

signed main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int t = 1;

    while (t--) AC();
}