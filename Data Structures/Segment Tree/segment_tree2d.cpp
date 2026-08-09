struct Node {
    int ign = 0, val;

    Node() : val(ign) {
    }

    Node(int x) : val(x) {
    }

    Node operator+(Node &r) {
        Node res = Node();
        res.val = val + r.val;
        return res;
    }
};

#define lNode (x * 2 + 1)
#define rNode (x * 2 + 2)
#define md (lx + (rx - lx) / 2)

struct Sagara {
    int n;
    vector<Node> node;

    Sagara(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        node.assign(n * 2, Node());
    }

    void set(int &ind, int &val, int x, int lx, int rx) {
        if (rx - lx == 1) {
            node[x] = Node(val);
            return;
        }
        if (ind < md) set(ind, val, lNode, lx, md);
        else set(ind, val, rNode, md, rx);
        node[x] = node[lNode] + node[rNode];
    }

    void set(int ind, int val) { set(ind, val, 0, 0, n); }
    Node get(int &i) { return node[n + i - 1]; }

    Node query(int &l, int &r, int x, int lx, int rx) {
        if (lx >= r || rx <= l) return Node();
        if (rx <= r && lx >= l) return node[x];
        Node L = query(l, r, lNode, lx, md);
        Node R = query(l, r, rNode, md, rx);
        return L + R;
    }

    Node query(int l, int r) { return query(l, r, 0, 0, n); }
};

struct Sagara2D {
    vector<Sagara> node;
    int n;

    Sagara2D(int _n, int _m) {
        n = 1;
        while (n < _n) n <<= 1;
        node.assign(n * 2, Sagara(_m));
    }

    void set(int i, int j, int val, int x, int lx, int rx) {
        if (rx - lx == 1)
            return node[x].set(j, val);
        if (i < md) set(i, j, val, lNode, lx, md);
        else set(i, j, val, rNode, md, rx);
        Node L = node[lNode].get(j);
        Node R = node[rNode].get(j);
        node[x].set(j, (L + R).val);
    }

    void set(int i, int j, int val) { set(i, j, val, 0, 0, n); }

    Node query(int t, int b, int l, int r, int x, int lx, int rx) {
        if (rx <= t || lx >= b) return Node();
        if (lx >= t && rx <= b) return node[x].query(l, r);
        Node L = query(t, b, l, r, lNode, lx, md);
        Node R = query(t, b, l, r, rNode, md, rx);
        return L + R;
    }

    //  tree.query(--x1 , x2 , --y1 , y2)
    int query(int t, int b, int l, int r) {
        return query(t, b, l, r, 0, 0, n).val;
    }
};