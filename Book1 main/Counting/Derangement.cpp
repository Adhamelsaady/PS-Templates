#include<bits/stdc++.h>

using namespace std;
#define int long long

/*
    ============================================================
    Derangements
    ============================================================

    A derangement is a permutation p of {1..n} such that:

        p[i] != i  for every i.

    Classic applications:
      - nobody receives their own gift
      - Secret Santa with no self-assignment
      - permutations with zero fixed points

    Recurrence:
        D[0] = 1
        D[1] = 0
        D[n] = (n-1) * (D[n-1] + D[n-2])

    The code below stores D[i] for all i <= n.

    NOTE:
    This original template assumes that a variable named `mod` is defined
    elsewhere. If this file is compiled standalone, define e.g.
        const int mod = 1e9 + 7;
    before using it.
*/

// Number of permutations of size n with no fixed point: p[i] != i.
vector<int> Derangement(int n) {
    // D[i] = number of derangements of i elements.
    vector<int> D(n + 1, 0);

    // For n >= 2:
    // D[2] = 1.
    // The vector is initialized with zeros, so D[0]=0/D[1]=0 in the
    // original template. Only D[2] and onward are explicitly needed by
    // the recurrence as written.
    D[2] = 1;

    // Recurrence:
    // Consider where element 1 goes. It can go to any of n-1 positions.
    // After fixing that choice, the remaining structure splits into the
    // standard D[n-1] / D[n-2] cases.
    for (int i = 3; i <= n; ++i) {
        D[i] = (i - 1) * (D[i - 1] + D[i - 2]) % mod;
    }

    return D;
}
