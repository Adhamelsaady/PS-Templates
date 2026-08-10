
struct Aho {
    int N, P;
    const int A = 26;
    vector<vector<int> > next;
    vector<int> link, out_link;
    vector<vector<int> > out;
    Aho() : N(0), P(0) { node(); }
    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }

    inline int get(char c) {
        return c - 'a';
    }

    void add(const string T, int idx) {
        int u = 0;
        for (auto c: T) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(idx);
    }

    void compute() {
        queue<int> q;
        for (q.push(0); !q.empty();) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    int advance(int u, char c) {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }

    string smallest(int L) {
        string res;
        int u = 0;
        for (int i = 0; i < L; i++) {
            for (int c = 0; c < 26; c++) {
                int v = next[u][c];
                if (out[v].empty()) {
                    res.push_back(char('a' + c));
                    u = v;
                    break;
                }
            }
        }
        return res;
    }
};

struct DynamicAC {
    vector<pair<Aho , vector<pair<string , int>>>> T;
    void add(string &t , int i) {
        vector<pair<string , int>> me {{t , i}};
        while (!T.empty() and me.size() == T.back().second.size()) {
            for (auto &t: T.back().second)
                me.emplace_back(t);

            T.pop_back();
        }

        Aho aho;
        for (auto &t: me)
            aho.add(t.first , t.second);
        aho.compute();
        T.emplace_back(aho, me);
    }

    int get (string &t) {
        int answer = 0;
        for (auto &[aho, cur]: T) {
            int u = 0;
            for (auto c: t) {
                u = aho.advance(u, c);
                for (int v = u; v; v = aho.out_link[v]) {
                    for (int j : aho.out[v]) answer += j;
                }
            }
        }
        return answer;
    }
};