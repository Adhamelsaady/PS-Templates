struct DynamicSagara {
    struct Node {
        int lc = -1, rc = -1;
        long long sum = 0, lazy = 0;
        bool isLazy = false;

        void apply(long long x, long long lx, long long rx) {
            sum += x * (rx - lx);
            lazy += x;
            isLazy = true;
        }
    };

    vector<Node> tree;
    const long long n;

    DynamicSagara(long long n, int max_nodes = 1e7) : n(n) {
        tree.reserve(max_nodes); 
        tree.push_back(Node());
    }

    int create_node() {
        tree.push_back(Node());
        return tree.size() - 1;
    }

    Node merge(const Node &a, const Node &b) {
        Node res;
        res.sum = a.sum + b.sum;
        return res;
    }

    void propagate(int u, long long lx, long long rx) {
        long long m = lx + (rx - lx) / 2;
        
        if (tree[u].lc == -1) tree[u].lc = create_node();
        if (tree[u].rc == -1) tree[u].rc = create_node();
        
        if (!tree[u].isLazy) return;

        tree[tree[u].lc].apply(tree[u].lazy, lx, m);
        tree[tree[u].rc].apply(tree[u].lazy, m, rx);

        tree[u].lazy = 0;
        tree[u].isLazy = false;
    }

    void update(long long l, long long r, long long val, int u, long long lx, long long rx) {
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            tree[u].apply(val, lx, rx);
            return;
        }
        
        propagate(u, lx, rx);
        long long m = lx + (rx - lx) / 2;
        
        update(l, r, val, tree[u].lc, lx, m);
        update(l, r, val, tree[u].rc, m, rx);

        tree[u].sum = merge(tree[tree[u].lc], tree[tree[u].rc]).sum;
    }

    Node query(long long l, long long r, int u, long long lx, long long rx) {
        if (lx >= r || rx <= l || u == -1) return Node(); 
        
        if (lx >= l && rx <= r) return tree[u];
        
        propagate(u, lx, rx);
        long long m = lx + (rx - lx) / 2;
        
        Node L = query(l, r, tree[u].lc, lx, m);
        Node R = query(l, r, tree[u].rc, m, rx);
        
        return merge(L, R); 
    }

    void update(long long l, long long r, long long val) { 
        update(l, r, val, 0, 0, n); 
    }

    long long query(long long l, long long r) { 
        return query(l, r, 0, 0, n).sum; 
    }
};