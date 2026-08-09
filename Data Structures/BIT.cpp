struct BIT {
    vector<int> Tree;
    int n;
    BIT(int _n) {
        n = _n + 1;
        Tree.assign(n, 0);
    }

    int merge(int &a , int &b) {
        return a + b;
    }

    void update(int idx, int val) {
        for (; idx < n; idx = idx | (idx + 1))
            Tree[idx] = merge(Tree[idx], val);
    }

    void update(int l, int r, int val) {
        update(l , val);
        update(r + 1, -val);
    }

    int query(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = merge(ret , Tree[r]);
        return ret;
    }

    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};