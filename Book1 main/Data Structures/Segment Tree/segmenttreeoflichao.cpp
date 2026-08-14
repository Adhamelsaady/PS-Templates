const ll INF = 2e18;
const ll MIN_X = 0, MAX_X = 1e9;

struct Line {
    ll m, c;
    Line(ll _m = 0, ll _c = INF) : m(_m), c(_c) {}
    ll get(ll x) const { return m * x + c; }
};

struct LiChaoTree {
    struct Node {
        Line line;
        int left = -1, right = -1;
    };

    vector<Node> tree;

    LiChaoTree() {
        tree.push_back(Node());
    }

    void add(Line nw, ll l = MIN_X, ll r = MAX_X, int u = 0) {
        ll mid = l + (r - l) / 2;
        bool lef = nw.get(l) < tree[u].line.get(l);
        bool midf = nw.get(mid) < tree[u].line.get(mid);

        if (midf) swap(tree[u].line, nw);
        if (l == r) return;

        if (lef != midf) {
            if (tree[u].left == -1) {
                tree[u].left = tree.size();
                tree.push_back(Node());
            }
            add(nw, l, mid, tree[u].left);
        } else {
            if (tree[u].right == -1) {
                tree[u].right = tree.size();
                tree.push_back(Node());
            }
            add(nw, mid + 1, r, tree[u].right);
        }
    }

    ll query(ll x, ll l = MIN_X, ll r = MAX_X, int u = 0) const {
        if (u == -1) return INF;
        ll res = tree[u].line.get(x);
        if (l == r) return res;

        ll mid = l + (r - l) / 2;
        if (x <= mid) return min(res, query(x, l, mid, tree[u].left));
        return min(res, query(x, mid + 1, r, tree[u].right));
    }
};

struct SegTreeOfLiChao {
    int n;
    vector<LiChaoTree> st;

    SegTreeOfLiChao(int _n) : n(_n) {
        st.resize(4 * n + 1);
    }

    void add_line(int node, int l, int r, int ql, int qr, Line line) {
        if (ql > r || qr < l) return; // ??? ??????

        if (ql <= l && r <= qr) {
            st[node].add(line);
            return;
        }

        int mid = l + (r - l) / 2;
        add_line(2 * node, l, mid, ql, qr, line);
        add_line(2 * node + 1, mid + 1, r, ql, qr, line);
    }

    ll query_min(int node, int l, int r, int idx, ll x) {
        ll res = st[node].query(x);

        if (l == r) return res;

        int mid = l + (r - l) / 2;
        if (idx <= mid) res = min(res, query_min(2 * node, l, mid, idx, x));
        else res = min(res, query_min(2 * node + 1, mid + 1, r, idx, x));

        return res;
    }

    void add(int ql, int qr, Line line) {
        add_line(1, 1, n, ql, qr, line);
    }

    ll get_min(int idx, ll x) {
        return query_min(1, 1, n, idx, x);
    }
};