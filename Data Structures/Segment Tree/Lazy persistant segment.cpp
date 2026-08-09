struct Node {
    int l = 0, r = 0;
    int val;
    int lazy;
    bool has_lazy;

    Node() {
        val = 0;
        lazy = 0;
        has_lazy = false;
    }

    explicit Node(int x) {
        val = x;
        lazy = 0;
        has_lazy = false;
    }
};

static Node merge(const Node &lf, const Node &ri) {
    Node res;
    res.val = lf.val + ri.val;
    return res;
}

static void apply_lazy(Node &node, int lazy_val, int len) {
    // Range Add:
    node.val += lazy_val * len;
    node.lazy += lazy_val;
    node.has_lazy = true;

    //  Range Set:
    // node.val = lazy_val * len;
    // node.lazy = lazy_val;
    // node.has_lazy = true;
}

static int combine_lazy(int parent_lazy, int child_lazy) {
    return parent_lazy + child_lazy; // Range Add

    // return parent_lazy;           // Range Set
}

struct PST {
    vector<Node> tree;
    int n;

    PST(int n, int max_nodes = 8000000) : n(n) {
        tree.reserve(max_nodes);
        tree.push_back(Node());
    }

    int copyNode(int old_idx) {
        tree.push_back(tree[old_idx]);
        return tree.size() - 1;
    }

    void push_down(int u, int lx, int rx) {
        if (!tree[u].has_lazy) return;

        int mid = lx + (rx - lx) / 2;
        int l_child = copyNode(tree[u].l);
        int r_child = copyNode(tree[u].r);

        apply_lazy(tree[l_child], tree[u].lazy, mid - lx + 1);
        apply_lazy(tree[r_child], tree[u].lazy, rx - mid);

        tree[u].l = l_child;
        tree[u].r = r_child;
        tree[u].has_lazy = false;
        tree[u].lazy = 0;
    }

    int build(const vector<int> &arr, int lx, int rx) {
        if (lx == rx) {
            int id = tree.size();
            tree.push_back(Node(arr[lx]));
            return id;
        }

        int mid = lx + (rx - lx) / 2;
        int l_child = build(arr, lx, mid);
        int r_child = build(arr, mid + 1, rx);

        int id = tree.size();
        Node res = merge(tree[l_child], tree[r_child]);
        res.l = l_child;
        res.r = r_child;
        tree.push_back(res);
        return id;
    }

    int build(const vector<int> &arr) {
        return build(arr, 0, n - 1);
    }

    int update(int prev_root, int l, int r, int val, int lx, int rx) {
        if (l > rx || r < lx) return prev_root;

        int u = copyNode(prev_root);

        if (l <= lx && r >= rx) {
            apply_lazy(tree[u], val, rx - lx + 1);
            return u;
        }

        push_down(u, lx, rx);

        int mid = lx + (rx - lx) / 2;
        tree[u].l = update(tree[u].l, l, r, val, lx, mid);
        tree[u].r = update(tree[u].r, l, r, val, mid + 1, rx);

        int old_lazy = tree[u].lazy;
        bool old_has_lazy = tree[u].has_lazy;
        int left_child = tree[u].l;
        int right_child = tree[u].r;

        tree[u] = merge(tree[left_child], tree[right_child]);
        tree[u].l = left_child;
        tree[u].r = right_child;
        tree[u].lazy = old_lazy;
        tree[u].has_lazy = old_has_lazy;

        return u;
    }

    int update(int prev_root, int l, int r, int val) {
        return update(prev_root, l, r, val, 0, n - 1);
    }

    Node query(int u, int l, int r, int lx, int rx, int pending_lazy, bool has_pending) {
        if (u == 0 || l > rx || r < lx) return Node();

        int current_lazy = pending_lazy;
        bool current_has = has_pending;

        if (tree[u].has_lazy) {
            if (current_has) {
                current_lazy = combine_lazy(pending_lazy, tree[u].lazy);
            } else {
                current_lazy = tree[u].lazy;
                current_has = true;
            }
        }

        if (l <= lx && r >= rx) {
            Node res = tree[u];
            if (has_pending) {
                apply_lazy(res, pending_lazy, rx - lx + 1);
            }
            return res;
        }

        int mid = lx + (rx - lx) / 2;
        Node L = query(tree[u].l, l, r, lx, mid, current_lazy, current_has);
        Node R = query(tree[u].r, l, r, mid + 1, rx, current_lazy, current_has);

        return merge(L, R);
    }

    int query(int root, int l, int r) {
        return query(root, l, r, 0, n - 1, 0, false).val;
    }
};