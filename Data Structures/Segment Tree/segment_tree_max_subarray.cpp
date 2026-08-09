struct Node {
    int prefix = 0, suffix = 0,val = 0,sum = 0;

    Node() {
    }

    explicit Node(int x) {
        val = sum = prefix = suffix = x;
    }

    void update(int x) {
        val -= x;
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
        res.sum = lf.sum + ri.sum;
        res.prefix = max(lf.prefix,lf.sum + ri.prefix);
        res.suffix = max(ri.suffix,ri.sum + lf.suffix);
        res.val = max({lf.val,ri.val,lf.suffix + ri.prefix});
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

    void set(int &idx, ll &val, int ni, int lx, int rx) {
        if (rx - lx == 1) return seg_data[ni].update(val);

        if (idx < md) set(idx, val, lNode, lx, md);
        else set(idx, val, rNode, md, rx);

        seg_data[ni] = merge(seg_data[lNode], seg_data[rNode]);
    }

    void set(int idx,int val) { set(idx, val, 0, 0, n); }

    Node get(int &l, int &r, int ni, int lx, int rx) {
        if (lx >= r || rx <= l) return Node();
        if (rx <= r && lx >= l) return seg_data[ni];

        Node L = get(l, r, lNode, lx, md);
        Node R = get(l, r, rNode, md, rx);

        return merge(L, R);
    }

    int get(int l,int r) { return get(l, r, 0, 0, n).val; }
};