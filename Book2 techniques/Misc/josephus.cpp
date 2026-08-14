#include <bits/stdc++.h>

using namespace std;
#define int long long

/*
    ================================================================
    JOSEPHUS PROBLEM - FIND THE LAST SURVIVOR
    ================================================================

    Problem pattern:
      n people stand in a circle. Starting from a position, every k-th
      alive person is removed. We want to know the last remaining person.

    The classic 0-based recurrence is:
        J(1, k) = 0
        J(n, k) = (J(n-1, k) + k) % n

    The simple recurrence costs O(n). This implementation uses a grouping
    optimization and is useful when n is huge and k is relatively small.

    IMPORTANT:
      - This function returns a 0-based index.
      - solve() adds 1 because the problem uses people numbered 1..n.
      - This template finds ONLY the survivor, not the whole elimination order.

    Typical applications:
      1) Classic Josephus / elimination-circle problems.
      2) Find the survivor when n is too large to simulate.
      3) Circular deletion problems where only the final remaining position
         is required.

    If the problem asks for the ENTIRE deletion order, use josephus_build.cpp
    (ordered_set / PBDS) instead.
*/

// Returns the 0-based index of the final survivor.
//
// Complexity of this optimized version is roughly O(k log n) for the
// intended regime where k is small. The recurrence is still exact.
int josephus(int n, int k) {
    // Only one person remains -> index 0.
    if (n == 1) return 0;

    // If we remove every 1st person, the last survivor is n-1 (0-based).
    if (k == 1) return n - 1;

    // When k > n, the first elimination does not allow the grouping
    // optimization below, so fall back to the standard recurrence.
    if (k > n)
        return (josephus(n - 1, k) + k) % n;

    // In one sweep, approximately n/k people are eliminated.
    // We remove these eliminations as a group and solve a smaller
    // Josephus problem of size n-cnt.
    int cnt = n / k;
    int res = josephus(n - cnt, k);

    // The smaller problem has a compressed indexing. Map its answer back
    // to the original circle. The following correction accounts for the
    // incomplete block n % k and then expands the compressed positions.
    res -= n % k;
    if (res < 0) res += n;
    else res += res / (k - 1);

    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;

    // josephus() is 0-based; problem people are numbered 1..n.
    cout << josephus(n, m) + 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef HALZOOM
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
#endif

    int test = 1;
    cin >> test;

    for (int i = 1; i <= test; ++i) {
        solve();
    }
    return 0;
}
