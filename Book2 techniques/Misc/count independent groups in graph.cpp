// Count independent sets by graph decomposition and branching
// Problem: Count all independent vertex sets of a graph. The program reads an adjacency matrix where '0' means no edge, so it builds the graph and recursively counts independent sets.
// Use: Input n (n<=50 in the intended bitmask representation) and an n*n 0/1 adjacency matrix. The answer includes the empty independent set.
// Variables: Key variables: g[v]=bitmask of neighbors; mask=current induced vertex set; comp=one connected component inside mask; f=first vertex used to find a component; best=branching vertex; md=maximum degree in current mask; r1/r2=counts excluding/including the chosen vertex; mp=memoization table.
// Idea: Identity: IS(G)=IS(G-v)+IS(G-v-N(v)). If G has disconnected components, IS(G)=product of their independent-set counts.
// Complexity: Complexity: exponential in the worst case; memoization and connected-component factorization make it practical for some sparse/small graphs. Memory is proportional to visited masks.

// this compute maximum numbers of clique for a graph G by getting G' and calcualte maximum number of indepenet set
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
ll g[50];
unordered_map<ll, ll> mp;

ll compOf(ll mask, int s) {
    ll comp = 0;
    ll st = (1LL << s);
    while (st) {
        int v = __builtin_ctzll(st);
        st &= st - 1;
        if ((comp >> v) & 1LL) continue;
        comp |= (1LL << v);
        ll neigh = g[v] & mask & ~comp;
        st |= neigh;
    }
    return comp;
}

ll dfs(ll mask) {
    if (mask == 0) return 1;
    auto it = mp.find(mask);
    if (it != mp.end()) return it->second;

    int f = __builtin_ctzll(mask);
    ll comp = compOf(mask, f);
    if (comp != mask) {
        ll a = dfs(comp);
        ll b = dfs(mask ^ comp);
        ll r = a * b;
        mp[mask] = r;
        return r;
    }

    int best = -1, md = -1;
    ll t = mask;
    while (t) {
        int u = __builtin_ctzll(t);
        t &= t - 1;
        int deg = __builtin_popcountll(g[u] & mask);
        if (deg > md) { md = deg; best = u; }
    }
    int v = best;
    ll without_v = mask & ~(1LL << v);
    ll r1 = dfs(without_v);
    ll r2 = dfs(without_v & ~g[v]);
    ll res = r1 + r2;
    mp[mask] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) {
        g[i] = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (a[i][j] == '0') g[i] |= (1LL << j);
        }
    }
    cout << dfs((1LL << n) - 1);
}
