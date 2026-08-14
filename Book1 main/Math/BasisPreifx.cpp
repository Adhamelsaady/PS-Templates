/**
 * Prefix / Range XOR Linear Basis.
 *
 * Each basis vector stores the latest array index that introduced its pivot.
 * Therefore a basis built for prefix [1..r] can answer queries [l..r] by
 * ignoring vectors whose stored index is < l.
 *
 * Typical problem: maximum XOR obtainable from any subset of a subarray [l,r].
 * Build: O(n * LOG), query: O(LOG).
 */
#include <bits/stdc++.h>

using namespace std;
const int lg = 32;

struct Basis {
    int size = 0;
    vector<int> basis, lst;

    Basis() {
        size = 0;
        basis.assign(lg, {});
        lst.assign(lg, -1);
// Test whether bit `bit` is set in n.
    };

    bool on(int n, int bit) {
        return n >> bit & 1;
// Insert n together with its original array index. Newer indices replace old
// representatives for the same pivot, which makes range queries possible.
    }

    bool insert(int n, int idx) {
        for (int i = lg - 1; ~i; --i) {
            if (!on(n, i))continue;
            if (lst[i] < idx) {
                if (lst[i] == -1)size++;
                swap(basis[i], n);
                swap(idx, lst[i]);
            }
            n ^= basis[i];
        }
        return false;
// Maximum XOR using only basis vectors whose stored index is >= idx.
    }

    int max_xor(int idx) {
        int answer = 0;
        for (int i = lg - 1; ~i; --i) {
            if (!basis[i] or lst[i] < idx or on(answer, i))continue;
            answer ^= basis[i];
        }
        return answer;
    }
// Build one prefix basis per array prefix, then answer [l,r] queries in O(LOG).
};

void solve() {
    int n;
    cin >> n;
    vector<Basis> T(n + 1);
    Basis add;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        add.insert(x, i);
        T[i] = add;
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << T[r].max_xor(l) << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef HALZOOM
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    int test = 1;
//    cin >> test;

    for (int i = 1; i <= test; ++i) {
        solve();
    }
    return 0;
}