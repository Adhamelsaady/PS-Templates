#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    Sliding Window Inversion Count

    For every window of length k, count pairs (i, j) such that:
        i < j and a[i] > a[j]

    Technique:
      - Coordinate compression
      - Fenwick tree storing frequencies of values in the current window

    When adding x to the right:
      new inversions = number of current values > x

    When removing x from the left:
      removed inversions = number of remaining values < x

    Complexity: O(n log n)
*/

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n = 0) { init(n); }

    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }

    void add(int idx, int delta) {
        for (++idx; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }

    int sumPrefix(int idx) const {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }

    int rangeSum(int l, int r) const {
        if (l > r) return 0;
        return sumPrefix(r) - (l ? sumPrefix(l - 1) : 0);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<int> vals = a;
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    vector<int> comp(n);
    for (int i = 0; i < n; ++i)
        comp[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();

    Fenwick fw((int)vals.size());
    ll inversions = 0;

    // Build first window.
    for (int i = 0; i < k; ++i) {
        int x = comp[i];
        inversions += fw.rangeSum(x + 1, (int)vals.size() - 1);
        fw.add(x, 1);
    }

    for (int l = 0; l + k <= n; ++l) {
        if (l) cout << ' ';
        cout << inversions;

        if (l + k == n) break;

        // Remove the leftmost element.
        int out = comp[l];
        fw.add(out, -1);
        inversions -= fw.rangeSum(0, out - 1);

        // Add the new rightmost element.
        int in = comp[l + k];
        inversions += fw.rangeSum(in + 1, (int)vals.size() - 1);
        fw.add(in, 1);
    }

    cout << '\n';
}
