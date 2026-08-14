#include <bits/stdc++.h>

using namespace std;
#define int long long

/*
    ================================================================
    PERMUTATION RANK / LEHMER CODE / K-TH UNRANKING
    ================================================================

    This template combines three important ideas:

      1) Lehmer code:
           permutation -> its lexicographic rank representation.

      2) Factorial number system:
           Lehmer digits are mixed-radix digits with bases
           n, n-1, ..., 1.

      3) Segment Tree order statistics:
           Find the k-th still-unused number in O(log n).

    The solve() function does:

        permutation A
             |
             v
        Lehmer code A
             |
             +----------------+
                              |
        permutation B         |
             |                |
             v                v
        Lehmer code B --> addOrders()
                              |
                              v
                      combined Lehmer code
                              |
                              v
                         Kth_Perm()
                              |
                              v
                         final permutation

    In other words, this template can be used for problems where we need
    to combine the lexicographic ranks of two permutations and reconstruct
    the permutation corresponding to the combined rank.

    IMPORTANT:
      The ranks here are 0-based. For n elements there are n! permutations,
      so valid ranks are 0 ... n!-1.

    Other applications of the same building blocks:
      - Find the lexicographic rank of a permutation.
      - Find the k-th lexicographic permutation.
      - Add/subtract permutation ranks.
      - Work with factorial number system representations.
      - Dynamic "k-th unused element" queries.
      - Order-statistics on a set of alive/unused positions.
*/

struct SegmentTree {
#define Lidx (2 * node + 1)
#define Ridx (2 * node + 2)
#define mid ((l + r) / 2)
private:
    vector<int> Seg;
    int SegSize = 1;

    // Merge two segments by counting how many elements are alive/available.
    int merge(int a, int b) {
        return a + b;
    }

    // Point update: set position idx to value v.
    // In this template, 1 = available and 0 = already used.
    void update(int l, int r, int node, int idx, int v) {
        if (l == r) {
            Seg[node] = v;
            return;
        }
        if (mid >= idx) update(l, mid, Lidx, idx, v);
        else update(mid + 1, r, Ridx, idx, v);
        Seg[node] = merge(Seg[Lidx], Seg[Ridx]);
    }

    // Range sum query: count available elements in [Lx, Rx].
    int query(int l, int r, int node, int Lx, int Rx) {
        if (l > Rx or r < Lx) return 0;
        if (l >= Lx and r <= Rx) return Seg[node];
        int Left = query(l, mid, Lidx, Lx, Rx);
        int Right = query(mid + 1, r, Ridx, Lx, Rx);
        return merge(Left, Right);
    }

    // Find the position of the k-th available element.
    // k is 1-based here:
    //   Kth(1) = first available position
    //   Kth(2) = second available position
    // We descend the tree according to the number of available elements
    // in the left child.
    int Kth(int l, int r, int node, int k) {
        if (l == r) return l;
        if (Seg[Lidx] >= k)
            return Kth(l, mid, Lidx, k);
        else
            return Kth(mid + 1, r, Ridx, k - Seg[Lidx]);
    }

public:
    SegmentTree(int n) {
        SegSize = 1;
        while (SegSize < n) SegSize *= 2;
        Seg.assign(2 * SegSize, 0);
    }

    // Public point update.
    void update(int idx, int v) { update(0, SegSize - 1, 0, idx, v); }

    // Public range query.
    int query(int l, int r) { return query(0, SegSize - 1, 0, l, r); }

    // Public k-th available element query (1-based k).
    int Kth(int k) { return Kth(0, SegSize - 1, 0, k); }

#undef Lidx
#undef Ridx
#undef mid
};

/*
    Add two Lehmer codes.

    Why is this NOT normal addition?
      A Lehmer code is a mixed-radix number.
      For an n-element permutation, the digit at position i has base
          radix = n - i
      so its valid range is [0, radix-1].

    Therefore we add from right to left exactly like normal addition,
    but each position uses a different base.

    Example for n = 4:
      bases are 4, 3, 2, 1.
      digit limits are:
        c[0] in [0,3]
        c[1] in [0,2]
        c[2] in [0,1]
        c[3] = 0

    Application:
      If a and b are Lehmer codes of two permutations, this function
      computes the Lehmer code corresponding to rank(a) + rank(b),
      assuming the resulting rank is still inside [0, n!-1].
*/
vector<int> addOrders(vector<int> &a, vector<int> &b) {
    int n = a.size();
    vector<int> c(n);
    int carry = 0;

    for (int i = n - 1; i >= 0; --i) {
        int radix = n - i;
        int sum = a[i] + b[i] + carry;

        // Store the digit in this mixed-radix position.
        c[i] = sum % radix;

        // Carry to the next (more significant) position.
        carry = sum / radix;
    }
    return c;
}

/*
    Convert a permutation into its Lehmer code.

    ord[i] = number of UNUSED elements smaller than a[i].

    Example:
        permutation = [2, 3, 1]

        i=0: smaller unused than 2 -> {1} -> 1
        i=1: smaller unused than 3 -> {1} -> 1
        i=2: -> 0

        Lehmer code = [1, 1, 0]

    Its rank is:
        1 * 2! + 1 * 1! + 0 * 0! = 3

    Applications:
      - Lexicographic rank of a permutation.
      - Convert a permutation to factorial number system.
      - Combine permutation ranks.

    Complexity:
      O(n log n)
*/
vector<int> getOrder(vector<int> &a) {
    int n = a.size();
    vector<int> ord(n);
    SegmentTree seg(n);

    // Initially every value 0..n-1 is available.
    for (int i = 0; i < n; ++i)
        seg.update(i, 1);

    for (int i = 0; i < n; ++i) {
        // a[i] is now being consumed, so remove it BEFORE querying.
        seg.update(a[i], 0);

        // Count still-unused values in [0, a[i]-1].
        // The query uses [0, a[i]], but a[i] has already been set to 0,
        // so the result is exactly the number of smaller unused values.
        ord[i] = seg.query(0, a[i]);
    }
    return ord;
}

/*
    Convert a Lehmer code back into a permutation.

    coff[i] tells us which available element to choose:
        coff[i] = 0 -> smallest available
        coff[i] = 1 -> second smallest available
        ...

    Segment Tree stores:
        1 -> number is still available
        0 -> number has already been selected

    We ask for coff[i] + 1 because SegmentTree::Kth() is 1-based.

    Applications:
      - K-th lexicographic permutation.
      - Unranking a permutation from its factorial-number-system code.
      - Reconstructing a permutation after rank arithmetic.

    Complexity:
      O(n log n)
*/
vector<int> Kth_Perm(vector<int> &coff) {
    int n = coff.size();
    vector<int> answer(n);

    SegmentTree seg(n + 1);

    // Initially values 0..n-1 are all unused.
    for (int i = 0; i < n; ++i)
        seg.update(i, 1);

    for (int i = 0; i < n; ++i) {
        // Lehmer digit is 0-based, Kth() expects 1-based rank.
        int idx = seg.Kth(coff[i] + 1);
        answer[i] = idx;

        // This value is no longer available for later positions.
        seg.update(idx, 0);
    }
    return answer;
}

void solve() {
    int n;
    cin >> n;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // Step 1: permutation -> Lehmer code.
    auto coff1 = getOrder(a);
    auto coff2 = getOrder(b);

    // Step 2: add their factorial-number-system representations.
    // This corresponds to adding their lexicographic ranks.
    auto coff = addOrders(coff1, coff2);

    // Step 3: convert the resulting Lehmer code back to a permutation.
    auto answer = Kth_Perm(coff);

    for (auto i: answer)
        cout << i << ' ';
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
