#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct Aho {
    int N, P;
    const int A = 26;
    vector<vector<int>> next;
    vector<int> link, out_link;
    vector<vector<int>> out;
    
    // Subtask 1-10 States
    vector<int> depth;      
    vector<bool> is_safe;   
    vector<int> bfs_order;  
    vector<vector<int>> fail_tree; 
    vector<int> match_cnt;  
    
    // NEW: Subtask 11-15 States
    vector<int> state_mask; // Tracks which patterns are matched (bitmask)
    vector<int> tin, tout;  // Euler tour entry/exit times
    int timer;

    Aho() { clear(); }

    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(vector<int>());
        depth.emplace_back(0);
        is_safe.emplace_back(true);
        fail_tree.emplace_back(vector<int>());
        match_cnt.emplace_back(0);
        state_mask.emplace_back(0); // Initialize bitmask
        tin.emplace_back(0);
        tout.emplace_back(0);
        return N++;
    }

    // Subtask 1: Fast Reset (Time: O(N * A))
    void clear() {
        for (int i = 0; i < N; ++i) {
            fill(next[i].begin(), next[i].end(), 0);
            out[i].clear();
            fail_tree[i].clear();
        }
        link.assign(1, 0);
        out_link.assign(1, 0);
        depth.assign(1, 0);
        is_safe.assign(1, true);
        match_cnt.assign(1, 0);
        state_mask.assign(1, 0);
        tin.assign(1, 0);
        tout.assign(1, 0);
        bfs_order.clear();
        timer = 0;
        N = 0;
        P = 0;
        node(); 
    }

    inline int get(char c) const { return c - 'a'; }

    // Insertion (Time: O(|T|))
    void add(const string& T, int idx) {
        int u = 0;
        for (char c : T) {
            int c_idx = get(c);
            if (!next[u][c_idx]) {
                int v = node();
                next[u][c_idx] = v;
                depth[v] = depth[u] + 1; 
            }
            u = next[u][c_idx];
        }
        out[u].push_back(idx);
        state_mask[u] |= (1 << idx); // Subtask 13: Set bitmask for this pattern
        P = max(P, idx + 1);
    }

    // Main Compute (Time: O(N * A))
    void compute() {
        queue<int> q;
        bfs_order.clear();
        for (int c = 0; c < A; ++c) {
            if (next[0][c]) q.push(next[0][c]);
        }
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            bfs_order.push_back(u); 
            
            is_safe[u] = is_safe[link[u]] && out[u].empty();
            match_cnt[u] = match_cnt[link[u]] + out[u].size();
            
            // Subtask 13 helper: Inherit matches from suffix link
            state_mask[u] |= state_mask[link[u]]; 

            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) {
                    next[u][c] = next[link[u]][c];
                } else {
                    link[v] = next[link[u]][c];
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    // Subtask 8: O(1) Advance (Time: O(1))
    inline int advance(int u, char c) const { return next[u][get(c)]; }

    // Subtask 2: Fast Boolean Check (Time: O(|S|))
    bool contains_any(const string& s) const {
        int u = 0;
        for (char c : s) {
            u = advance(u, c);
            if (!is_safe[u]) return true; 
        }
        return false;
    }

    // Subtask 3: Linear Pattern Frequency Counting (Time: O(|S| + N))
    vector<int> pattern_frequencies(const string& s) const {
        vector<int> state_hits(N, 0);
        int u = 0;
        for (char c : s) {
            u = advance(u, c);
            state_hits[u]++;
        }
        vector<int> ans(P, 0);
        for (int i = (int)bfs_order.size() - 1; i >= 0; --i) {
            int curr = bfs_order[i];
            state_hits[link[curr]] += state_hits[curr];
            for (int idx : out[curr]) ans[idx] += state_hits[curr];
        }
        return ans;
    }

    // Subtask 4 & 15: Suffix Link Tree & Euler Tour (Time: O(N))
    // Useful for offline queries (e.g., placing text matches in a Fenwick Tree)
    void build_fail_tree_and_tour() {
        for (int i = 0; i < N; ++i) fail_tree[i].clear();
        for (int i = 1; i < N; ++i) fail_tree[link[i]].push_back(i);
        timer = 0;
        dfs_fail(0);
    }

    void dfs_fail(int u) {
        tin[u] = ++timer;
        for (int v : fail_tree[u]) dfs_fail(v);
        tout[u] = timer;
    }

    // Subtask 5: Extract Transition Matrix (Time: O(N * A))
    vector<vector<long long>> get_transition_matrix() const {
        vector<vector<long long>> mat(N, vector<long long>(N, 0));
        for (int u = 0; u < N; ++u) {
            if (!is_safe[u]) continue;
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (is_safe[v]) mat[u][v]++;
            }
        }
        return mat;
    }

    // Subtask 6: Lexicographically Smallest Avoiding String (Time: O(L * A))
    string smallest(int L) const {
        string res;
        int u = 0;
        for (int i = 0; i < L; i++) {
            for (int c = 0; c < 26; c++) {
                int v = next[u][c];
                if (is_safe[v]) {
                    res.push_back(char('a' + c));
                    u = v;
                    break;
                }
            }
            if (res.size() == i) return ""; 
        }
        return res;
    }

    // Subtask 7: Count Total Overlapping Matches (Time: O(|S|))
    long long count_total_matches(const string& s) const {
        long long total = 0, u = 0;
        for (char c : s) {
            u = advance(u, c);
            total += match_cnt[u];
        }
        return total;
    }

    // Subtask 9: First Occurrence of Each Pattern (Time: O(|S| + Matches))
    vector<int> first_occurrence(const string& s) const {
        vector<int> first(P, -1);
        int u = 0;
        for (int i = 0; i < s.size(); ++i) {
            u = advance(u, s[i]);
            for (int v = u; v; v = out_link[v]) {
                for (int idx : out[v]) {
                    if (first[idx] == -1) first[idx] = i - depth[v] + 1; 
                }
            }
        }
        return first;
    }

    // Subtask 10: Get Positions of All Patterns (Time: O(|S| + Matches))
    vector<vector<int>> getPositions(const string& s) const {
        vector<vector<int>> Where(s.size());
        int u = 0, i = 0;
        for (char c : s) {
            u = advance(u, c);
            for (int v = u; v; v = out_link[v]) {
                for (int x : out[v]) Where[i - depth[v] + 1].emplace_back(x);
            }
            ++i;
        }
        return Where;
    }

    // Subtask 11: Count Valid Strings of Length L (Time: O(L * N * A))
    // DP on the automaton to count strings of length L avoiding all dict words
    int count_safe_strings(int L, int MOD) const {
        vector<long long> dp(N, 0);
        dp[0] = 1;
        for (int i = 0; i < L; ++i) {
            vector<long long> next_dp(N, 0);
            for (int u = 0; u < N; ++u) {
                if (!is_safe[u] || !dp[u]) continue;
                for (int c = 0; c < A; ++c) {
                    int v = next[u][c];
                    if (is_safe[v]) {
                        next_dp[v] = (next_dp[v] + dp[u]) % MOD;
                    }
                }
            }
            dp = next_dp;
        }
        long long ans = 0;
        for (int u = 0; u < N; ++u) ans = (ans + dp[u]) % MOD;
        return ans;
    }

    // Subtask 12: Minimum Words to Form Text (Word Break Problem) (Time: O(|S| + Matches))
    // Returns the minimum dictionary words needed to concatenate into string S (-1 if impossible)
    int min_words_to_form(const string& s) const {
        int n = s.length();
        vector<int> dp(n + 1, 1e9); // dp[i] = min words to form s[0...i-1]
        dp[0] = 0;
        int u = 0;
        
        for (int i = 0; i < n; ++i) {
            u = advance(u, s[i]);
            // If we can't even reach the current prefix, no point checking transitions
            if (dp[i + 1 - depth[u]] == 1e9 && dp[i] == 1e9) continue; 
            
            for (int v = u; v; v = out_link[v]) {
                if (!out[v].empty()) {
                    dp[i + 1] = min(dp[i + 1], dp[i + 1 - depth[v]] + 1);
                }
            }
        }
        return dp[n] == 1e9 ? -1 : dp[n];
    }

    // Subtask 14: Shortest String Containing ALL Patterns (Time: O(N * A * 2^P))
    // TSP DP using BFS on the automaton. NOTE: ONLY USE IF P <= 20!
    string shortest_containing_all() const {
        if (P > 20) return ""; // Too many patterns for bitmask DP
        
        int target_mask = (1 << P) - 1;
        vector<vector<int>> dist(N, vector<int>(1 << P, 1e9));
        vector<vector<pair<int, int>>> parent(N, vector<pair<int, int>>(1 << P, {-1, -1}));
        vector<vector<char>> parent_char(N, vector<char>(1 << P, 0));
        
        queue<pair<int, int>> q;
        q.push({0, 0});
        dist[0][0] = 0;
        
        int end_u = -1, end_mask = -1;
        
        while (!q.empty()) {
            auto [u, mask] = q.front(); q.pop();
            
            if (mask == target_mask) {
                end_u = u; 
                end_mask = mask;
                break; // BFS guarantees shortest path
            }
            
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                int nmask = mask | state_mask[v]; // Subtask 13 implementation used here
                
                if (dist[v][nmask] == 1e9) {
                    dist[v][nmask] = dist[u][mask] + 1;
                    parent[v][nmask] = {u, mask};
                    parent_char[v][nmask] = c + 'a';
                    q.push({v, nmask});
                }
            }
        }
        
        if (end_u == -1) return ""; // Not possible to form
        
        // Reconstruct string backwards
        string res = "";
        while (end_u != 0 || end_mask != 0) {
            res += parent_char[end_u][end_mask];
            auto p = parent[end_u][end_mask];
            end_u = p.first; 
            end_mask = p.second;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};