#include <bits/stdc++.h>
using namespace std;

/*
    Sliding Window MEX

    MEX = smallest non-negative integer missing from the window.

    Observation:
      For a window of size k, the MEX is always in [0, k].

    Maintain:
      - freq[x] for x in [0, k]
      - a set of currently missing values

    Complexity: O(n log k)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    vector<int> freq(k + 1, 0);
    set<int> missing;
    for (int x = 0; x <= k; ++x)
        missing.insert(x);

    auto add = [&](long long x) {
        if (0 <= x && x <= k) {
            int v = (int)x;
            if (freq[v] == 0) missing.erase(v);
            ++freq[v];
        }
    };

    auto remove = [&](long long x) {
        if (0 <= x && x <= k) {
            int v = (int)x;
            --freq[v];
            if (freq[v] == 0) missing.insert(v);
        }
    };

    for (int i = 0; i < k; ++i)
        add(a[i]);

    for (int l = 0; l + k <= n; ++l) {
        if (l) cout << ' ';
        cout << *missing.begin();

        if (l + k == n) break;

        remove(a[l]);
        add(a[l + k]);
    }

    cout << '\n';
}
