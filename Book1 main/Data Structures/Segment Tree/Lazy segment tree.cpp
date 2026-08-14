struct Node {
    int lazy = 0;
    bool is_lazy = 0;
    int val;

    Node() {
        val = 0;
    }

    explicit Node(int x) {
        val = x;
    }

    void update(int x,int lx,int rx) {
        val += x * (rx - lx);
        lazy += x;
        is_lazy = 1;
    }
};

#define lNode (ni * 2 + 1)
#define rNode (ni * 2 + 2)
#define md (lx + (rx - lx) / 2)

struct SegTree {
    vector<Node> seg_data;
    int n;

    explicit SegTree(int size) {
        n = 1;
        while (n < size) n *= 2;
        seg_data.resize(2 * n, Node());
    }

    static Node merge(Node &lf, Node &ri) {
        Node res;
        res.val = lf.val + ri.val;
        return res;
    }

    void build(vector<int> &v, int ni, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < v.size()) seg_data[ni] = Node(v[lx]);
            return;
        }

        build(v, lNode, lx, md);
        build(v, rNode, md, rx);
        seg_data[ni] = merge(seg_data[lNode], seg_data[rNode]);
    }

    void build(vector<int> &v) { build(v, 0, 0, n); }

    void propagate(int ni, int lx, int rx) {
        if (rx - lx == 1 || !seg_data[ni].is_lazy) return;

        seg_data[lNode].update(seg_data[ni].lazy, lx, md);
        seg_data[rNode].update(seg_data[ni].lazy, md, rx);

        seg_data[ni].is_lazy = seg_data[ni].lazy = 0;
    }

    void set(int l, int r, int val, int ni, int lx, int rx) {
        propagate(ni, lx, rx);

        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) return seg_data[ni].update(val, lx, rx);

        set(l, r, val, lNode, lx, md);
        set(l, r, val, rNode, md, rx);

        seg_data[ni] = merge(seg_data[lNode], seg_data[rNode]);
    }

    void set(int l, int r, int val) { set(l, r, val, 0, 0, n); }

    Node get(int &l, int &r, int ni, int lx, int rx) {
        propagate(ni, lx, rx);

        if (lx >= r || rx <= l) return Node();
        if (rx <= r && lx >= l) return seg_data[ni];

        Node L = get(l, r, lNode, lx, md);
        Node R = get(l, r, rNode, md, rx);

        return merge(L, R);
    }

    int get(int l,int r) { return get(l, r, 0, 0, n).val; }
};