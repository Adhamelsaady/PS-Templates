#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    Sliding Window XOR

    XOR is self-inverse:
        x ^ x = 0

    So when the window moves:
      - XOR in the new element
      - XOR out the old element

    Complexity: O(n)
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    ll x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;

    vector<ll> window(k);

    ll current = x;
    ll windowXor = 0;
    ll answer = 0;

    for (int i = 0; i < n; ++i) {
        if (i > 0)
            current = (current * a + b) % c;

        int pos = i % k;

        if (i >= k)
            windowXor ^= window[pos];

        window[pos] = current;
        windowXor ^= current;

        if (i >= k - 1)
            answer ^= windowXor;
    }

    cout << answer << '\n';
}
