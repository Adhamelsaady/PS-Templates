#include <bits/stdc++.h>

using namespace std;

/*
    ============================================================
    Dynamic counting of subsets by their exact GCD
    ============================================================

    We maintain an array a[1..n] and answer two kinds of queries:

      1 x
        What is the probability that a uniformly random NON-EMPTY subset
        has gcd exactly x?

      2 pos newValue
        Change a[pos] to newValue.

    MOD = 998244353.

    ------------------------------------------------------------
    Core counting idea
    ------------------------------------------------------------

    Let cnt[x] = number of array elements divisible by x.

    Any non-empty subset consisting only of numbers divisible by x has:
        2^(cnt[x]) - 1
    possibilities.

    But this includes subsets whose exact gcd is 2x, 3x, 4x, ... .
    Therefore process x from large to small:

        dp[x] = 2^(cnt[x]) - 1 - sum(dp[multiple])

    After this subtraction, dp[x] is exactly the number of non-empty
    subsets whose gcd is x.

    The probability is then:

        dp[x] / (2^n - 1)

    ------------------------------------------------------------
    Dynamic updates
    ------------------------------------------------------------

    If a value m is inserted/removed, cnt[d] changes for every divisor d of m.
    So we precompute all divisors in Div[value].

    When dp[d] changes, it also contributes to sumDp[x] for every proper
    divisor x of d. This lets us update the affected states without rebuilding
    the entire O(MAX log MAX) DP after every query.
*/

const int N = 1e5 + 5, mod = 998244353;

// dp[x] = number of non-empty subsets whose exact gcd is x.
int dp[N];

// sumDp[x] = sum of dp[m] over all proper multiples m of x.
// This is kept so dp[x] can be recomputed quickly after updates.
int sumDp[N];

// frq[x] = number of current array elements divisible by x.
int frq[N];

// pw[i] = 2^i mod MOD.
int pw[N];

// Div[x] = all divisors of x.
// Used to update every divisor affected by inserting/removing a value.
vector<int> Div[N];

// Fast modular exponentiation: base^pow mod MOD.
int exp(int base, int pow) {
    if (pow < 0) return 0;

    int res = 1;
    while (pow) {
        if (pow & 1)
            res = 1ll * res * base % mod;

        base = 1ll * base * base % mod;
        pow >>= 1;
    }

    return res;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);

    // Precompute powers of 2 up to n.
    pw[0] = 1;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];

        // Initially count exact values. Later we convert these counts into
        // counts of numbers divisible by each x using the multiples loop.
        frq[a[i]]++;

        pw[i] = pw[i - 1] * 2 % mod;
    }

    // Convert exact frequency into frequency of multiples:
    // frq[i] = number of a[j] such that i divides a[j].
    // Example: if the array contains 6, then it contributes to frq[1], frq[2],
    // frq[3], and frq[6].
    for (int i = 1; i < N; ++i)
        for (int j = 2 * i; j < N; j += i)
            frq[i] += frq[j];

    // Compute exact-GCD counts from large gcd values down to 1.
    for (int i = N - 1; i; --i) {
        // Number of all non-empty subsets made only from elements divisible by i.
        dp[i] = pw[frq[i]] - 1;

        // Remove subsets whose exact gcd is a proper multiple of i.
        for (int j = 2 * i; j < N; j += i) {
            dp[i] -= dp[j];

            // Keep the sum of dp[multiple] so future updates can recompute dp[i]
            // in O(number of multiples/divisors) instead of scanning everything.
            sumDp[i] += dp[j];

            if (dp[i] < 0) dp[i] += mod;
            if (sumDp[i] >= mod) sumDp[i] -= mod;
        }
    }

    // Insert or remove one value m from the current array.
    // op = +1 -> insert m
    // op = -1 -> remove m
    //
    // Only divisors of m have their frq changed.
    auto update = [&](int m, int op = 1) {
        for (auto d : Div[m]) {
            // Since m is divisible by d, adding/removing m changes the number
            // of array elements divisible by d.
            frq[d] += op;

            // Save the old exact-GCD answer because all proper divisors of d
            // need to know how much dp[d] changed.
            int old = dp[d];

            // Recompute dp[d] from:
            //   all non-empty subsets of elements divisible by d
            //   minus all subsets whose exact gcd is a proper multiple of d.
            dp[d] = pw[frq[d]] - 1 - sumDp[d];
            if (dp[d] < 0) dp[d] += mod;

            // dp[d] is a multiple of every proper divisor `div` of d.
            // Therefore its change must be reflected in sumDp[div].
            for (auto div : Div[d]) {
                if (div == d) continue;

                sumDp[div] += dp[d] - old;

                if (sumDp[div] < 0) sumDp[div] += mod;
                if (sumDp[div] >= mod) sumDp[div] -= mod;
            }
        }
    };

    // Number of non-empty subsets is 2^n - 1.
    // Its modular inverse lets us turn the exact count dp[x] into a probability.
    int total = exp(pw[n] - 1, mod - 2);

    int q;
    cin >> q;

    while (q--) {
        int t, x, g;
        cin >> t >> x;

        if (t == 1) {
            // Probability that a random non-empty subset has gcd exactly x:
            //     dp[x] / (2^n - 1)
            cout << 1ll * dp[x] * total % mod << '\n';
        }
        else {
            // Update query:
            //     a[x] = g
            cin >> g;

            if (g == a[x]) continue;

            // Remove the old value from all divisor counts / gcd states.
            update(a[x], -1);

            // Change the array value.
            a[x] = g;

            // Add the new value to all divisor counts / gcd states.
            update(a[x], 1);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef HALZOOM
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    // Precompute all divisors for every value.
    // Div[j] will contain every divisor of j.
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i)
            Div[j].emplace_back(i);

        // Reverse so divisors are processed from large to small.
        // This ordering is useful for the update dependencies in the DP.
        reverse(Div[i].begin(), Div[i].end());
    }

    int test = 1;
    // cin >> test;

    for (int i = 1; i <= test; ++i)
        solve();

    return 0;
}
