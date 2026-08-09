#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
#define int long long
#define endl "\n"
//-------------------\\

const int oo = 2e18;

struct Node {
    int val;

    Node() {
        val = oo;
    }

    explicit Node(int x) {
        val = x;
    }

    void update(int x) {
        val += x;
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
        res.val = min(lf.val, ri.val);
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

    int nxt_smaller (int l,int r,int x, int ni, int lx,int rx) {
        if (lx >= r || rx <= l) return -1;

        int cur = seg_data[ni].val;
        if (cur > x) return -1;
        if (rx - lx == 1) return lx;
        int L = nxt_smaller(l,r,x,lNode,lx,md);
        if (L != -1) return L;
        return nxt_smaller(l,r,x,rNode,md,rx);

    }

    int nxt_smaller(int l,int r,int x) {
        return nxt_smaller(l,r,x,0,0,n);
    }
};



void solve() {
    int n,q; cin >> n >> q;
    vector<int> v(n); for (int i = 0; i < n;i++) cin >> v[i];
    SegTree st(n); st.build(v);
    while (q--) {
        int val,l,r; cin >> val >> l >> r;
        l--,r--;
        int cur = st.nxt_smaller(l,r+1,val);
        while (cur <= r and cur != -1) {
            val %= v[cur];
            cur = st.nxt_smaller(l,r+1,val);
        }
        cout << val << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(9);
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
