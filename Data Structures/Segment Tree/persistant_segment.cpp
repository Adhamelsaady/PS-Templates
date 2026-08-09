struct Node {
    int l = 0, r = 0;
    int val;

    Node() {
        val = 0;
    }

    explicit Node(int x) {
        val = x;
    }
};

static Node merge(const Node &lf, const Node &ri) {
    Node res;
    res.val = lf.val + ri.val; 
    return res;
}

static void apply(Node &node, int x) {
    node.val += x; // Add
    // node.val = x; // Set
}

struct PST {
    vector<Node> tree;
    int n;

    PST(int n, int max_nodes = 4000000) : n(n) {
        tree.reserve(max_nodes);
        tree.push_back(Node()); // Dummy node (idx 0)
    }

    int createLeaf(int old_node_idx, int val) {
        Node res = tree[old_node_idx]; 
        apply(res, val);               
        tree.push_back(res);
        return tree.size() - 1;
    }

    int createLeafFromVal(int val) {
        tree.push_back(Node(val));
        return tree.size() - 1;
    }

    int createNode(int l_child, int r_child) {
        Node res = merge(tree[l_child], tree[r_child]);
        res.l = l_child;
        res.r = r_child;
        tree.push_back(res);
        return tree.size() - 1;
    }

    int build(const vector<int> &arr, int lx, int rx) {
        if (lx == rx) {
            return createLeafFromVal(arr[lx]);
        }

        int mid = lx + (rx - lx) / 2;
        int l_child = build(arr, lx, mid);
        int r_child = build(arr, mid + 1, rx);

        return createNode(l_child, r_child);
    }

    int build(const vector<int> &arr) {
        return build(arr, 0, n - 1);
    }

    int update(int prev_root, int i, int val, int lx, int rx) {
        if (lx == rx) {
            return createLeaf(prev_root, val);
        }

        int mid = lx + (rx - lx) / 2;
        int l_child = tree[prev_root].l;
        int r_child = tree[prev_root].r;

        if (i <= mid) {
            l_child = update(l_child, i, val, lx, mid);
        } else {
            r_child = update(r_child, i, val, mid + 1, rx);
        }

        return createNode(l_child, r_child);
    }

    int update(int prev_root, int i, int val) {
        return update(prev_root, i, val, 0, n - 1);
    }

    Node query(int u, int l, int r, int lx, int rx) {
        if (u == 0 || l > rx || r < lx) return Node();
        if (l <= lx && r >= rx) return tree[u];

        int mid = lx + (rx - lx) / 2;
        Node L = query(tree[u].l, l, r, lx, mid);
        Node R = query(tree[u].r, l, r, mid + 1, rx);

        return merge(L, R);
    }

    int query(int root, int l, int r) {
        return query(root, l, r, 0, n - 1).val;
    }

    int getKth(int u_L, int u_R, int k, int lx, int rx) {
        if (lx == rx) return lx;

        int count_left = tree[tree[u_R].l].val - tree[tree[u_L].l].val;
        int mid = lx + (rx - lx) / 2;

        if (count_left >= k) {
            return getKth(tree[u_L].l, tree[u_R].l, k, lx, mid);
        } else {
            return getKth(tree[u_L].r, tree[u_R].r, k - count_left, mid + 1, rx);
        }
    }

    int getKth(int version_L, int version_R, int k) {
        return getKth(version_L, version_R, k, 0, n - 1);
    }
};