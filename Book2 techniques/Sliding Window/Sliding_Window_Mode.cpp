#include <bits/stdc++.h>
using namespace std;

/*
    Sliding Window Mode

    For each window:
      - return the value with maximum frequency
      - if tied, return the smallest value

    Maintain:
      freq[x] = frequency of x in the current window
      order    = set of (-frequency, value)

    Then *order.begin() is always the answer.

    Complexity: O(n log k)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    map<int, int> freq;
    set<pair<int, int>> order; // (-frequency, value)

    auto add = [&](int x) {
        if (freq[x] > 0)
            order.erase({-freq[x], x});

        ++freq[x];
        order.insert({-freq[x], x});
    };

    auto remove = [&](int x) {
        order.erase({-freq[x], x});

        --freq[x];
        if (freq[x] == 0) {
            freq.erase(x);
        } else {
            order.insert({-freq[x], x});
        }
    };

    for (int i = 0; i < k; ++i)
        add(a[i]);

    for (int l = 0; l + k <= n; ++l) {
        if (l) cout << ' ';
        cout << order.begin()->second;

        if (l + k == n) break;

        remove(a[l]);
        add(a[l + k]);
    }

    cout << '\n';
}
