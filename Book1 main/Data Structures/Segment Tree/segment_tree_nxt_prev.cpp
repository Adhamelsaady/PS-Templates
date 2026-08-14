#define lNode (x * 2 + 1)
#define rNode (x * 2 + 2)
#define md (lx + (rx - lx) / 2)

const int oo = 2e8;

struct Node {
    int mx = -oo, mn = oo;

    Node() {
    }

    Node(int x) : mx(x), mn(x) {
    }

    void set(int x) { mx = mn = x; }
};

struct Sagara {
    int n;
    vector<Node> node;

    Sagara(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        node.assign(n * 2, {});
    }

    Node merge(Node& l, Node& r) {
        Node res;
        res.mx = max(l.mx, r.mx);
        res.mn = min(l.mn, r.mn);
        return res;
    }

    void build(vector<int>& v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < v.size()) node[x] = Node(v[lx]);
            return;
        }

        build(v, lNode, lx, md), build(v, rNode, md, rx);
        node[x] = merge(node[lNode], node[rNode]);
    }

    void build(vector<int>& v) { build(v, 0, 0, n); }

    void set(int& ind, ll& val, int x, int lx, int rx) {
        if (rx - lx == 1) return node[x].set(val);
        if (ind < md) set(ind, val, lNode, lx, md);
        else set(ind, val, rNode, md, rx);
        node[x] = merge(node[lNode], node[rNode]);
    }

    void set(int ind, ll val) { set(ind, val, 0, 0, n); }

    int nxt_greater(int l, int val, int x, int lx, int rx) {
        // change the condition (l included)
        if (node[x].mx < val || rx <= l) return -1;
        if (rx - lx == 1) return lx;
        int ans = nxt_greater(l, val, lNode, lx, md);
        if (~ans) return ans;
        return nxt_greater(l, val, rNode, md, rx);
    }

    int nxt_greater(int l, int val) { return nxt_greater(l, val, 0, 0, n); }

    int nxt(int l, int val, int x, int lx, int rx) {
        // change the condition (l included)
        if (node[x].mn > val || rx <= l) return -1;
        if (rx - lx == 1) return lx;
        int ans = nxt(l, val, lNode, lx, md);
        if (~ans) return ans;
        return nxt(l, val, rNode, md, rx);
    }

    int nxt(int l, int val) { return nxt(l, val, 0, 0, n); }

    int prev(int r, int val, int x, int lx, int rx) {
        // change the condition (r included)
        if (node[x].mx < val || lx > r) return -1;
        if (rx - lx == 1) return lx;
        int ans = prev(r, val, rNode, md, rx);
        if (~ans) return ans;
        return prev(r, val, lNode, lx, md);
    }

    int prev(int r, int val) { return prev(r, val, 0, 0, n); }
};