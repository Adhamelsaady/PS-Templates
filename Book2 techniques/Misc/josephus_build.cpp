#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
#define int long long

/*
    ================================================================
    JOSEPHUS - BUILD / PRINT THE WHOLE ELIMINATION ORDER
    ================================================================

    Use this template when the problem asks for the sequence of people
    removed, not just the final survivor.

    Data structure:
      PBDS ordered_set

    Why?
      We need two operations repeatedly:
        1) Find the k-th ALIVE person.
        2) Delete that person.

      A normal vector cannot do both efficiently because deletion can be
      O(n). PBDS supports both in O(log n).

    Useful PBDS operations:
      order_of_key(x)
          = number of elements strictly smaller than x.

      find_by_order(k)
          = iterator to the k-th element, where k is 0-based.
          find_by_order(0) -> smallest element.
          find_by_order(1) -> second smallest, etc.

    Applications:
      1) Josephus elimination order.
      2) Circular deletion problems.
      3) "Remove the k-th alive element" problems.
      4) K-th alive / K-th remaining element after many deletions.
      5) Dynamic order statistics where we need deletion + k-th query.

    Complexity:
      Build: O(n log n)
      Each deletion + find_by_order: O(log n)
      Total: O(n log n)

    NOTE ABOUT OFF-BY-ONE:
      This code uses:
          pos = (pos + m) % alive_count;
      This corresponds to the exact counting convention used by this
      template. Some Josephus statements use (pos + m - 1), so always
      verify whether the current person counts as 1 before copying it.
*/

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// order_of_key(k): number of elements strictly smaller than k - O(log n)
// find_by_order(k): iterator to the k-th element, k is 0-based - O(log n)

void solve() {
    int n, m;
    cin >> n >> m;

    // Store all currently alive people.
    ordered_set<int> st;
    for (int i = 1; i <= n; i++)
        st.insert(i);

    // pos is the 0-based rank among the currently alive people.
    int pos = 0;

    for (int i = 1; i <= n; i++) {
        int alive = n - i + 1;

        // Move m positions in the CURRENT ordered set.
        // Because pos is a rank, modulo alive keeps it inside the set.
        pos = (pos + m) % alive;

        // Get the person with this rank among the alive people.
        auto it = st.find_by_order(pos);

        // Print and remove that person.
        cout << *it << " ";
        st.erase(it);
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
