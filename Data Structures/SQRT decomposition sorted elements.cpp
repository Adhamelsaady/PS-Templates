
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
// #define int long long
#define endl "\n"
//-------------------\\

constexpr int mod = 1e9 + 7, oo = 2e8, N = 6e6 + 5;

vector<int> arr;
vector<vector<int>> sqrt_decomposition;

int sq;

void build()
{
    int n = arr.size();
    sq = ceil(sqrt(n));

    sqrt_decomposition.assign(sq, {});

    for (int i = 0; i < n; ++i) {
        sqrt_decomposition[i / sq].push_back(arr[i]);
    }

    for(auto & SD : sqrt_decomposition) sort(SD.begin(), SD.end());
}

int query(int l, int r, int v) // 0 indexed range
{
    int ans = 0;
    while (l % sq && l <= r) {
        /* check every arr[l] alone*/
        ans += arr[l] >= v;
        l++;
    }
    while (l + sq - 1 <= r) {
        /* check the block i and get answer from it */
        auto &SD = sqrt_decomposition[l/sq];
        int cnt = SD.end() - lower_bound(SD.begin(),SD.end(), v);
        ans += cnt;
        l += sq;
    }
    while (l <= r) {
        /* check every arr[l] alone*/
        ans += arr[l] >= v;
        l++;
    }

    return ans;
}

void update(int idx, long long val) // 0 indexed
{
    vector<int> &SD = sqrt_decomposition[idx / sq];
    SD[lower_bound(SD.begin(), SD.end(), arr[idx]) - SD.begin()] = val;
    arr[idx] = val;

    for (int i = 0; i < SD.size() - 1; ++i) {
        if(SD[i] > SD[i + 1]) swap(SD[i], SD[i + 1]);
    }
    for (int i = SD.size() - 1; i > 0; --i) {
        if(SD[i] < SD[i - 1]) swap(SD[i], SD[i - 1]);
    }
}

void solve() {
    int n; cin >> n;
    arr.assign(n,{});
    for (int i = 0; i < n; i++) cin >> arr[i];
    build();
    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t == 0) {
            int l,r,num; cin >> l >> r >> num;
            cout << query(--l,--r,num) << endl;
        }
        else {
            int idx,val; cin >> idx >> val;
            update(--idx,val);
        }
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
