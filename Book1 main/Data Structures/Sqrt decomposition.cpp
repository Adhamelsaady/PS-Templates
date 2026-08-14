struct SqrtDecomp {
    int n, SQ;
    vector<int> a, block;
    SqrtDecomp(int n): n(n) {
        SQ = sqrt(n) + 1;
        a.assign(n, 0);
        block.assign(SQ, 0);
    }

    void build(const vector<int>& arr) {
        a = arr;
        for (int i = 0; i < n; i++) {
            block[i / SQ] ^= a[i];
        }
    }

    // point update
    void update(int x, int val) {
        block[x / SQ] ^= a[x];   // remove old value
        a[x] ^= val;            // update element
        block[x / SQ] ^= a[x];   // add new value
    }

    // range query: sum in [l, r]
    int query(int l, int r) {
        int ans = 0;
        while (l <= r && l % SQ != 0) ans ^= a[l++];
        while (l + SQ - 1 <= r) {
            ans ^= block[l / SQ];
            l += SQ;
        }
        while (l <= r) ans ^= a[l++];
        return ans;
    }
};