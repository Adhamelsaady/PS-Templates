#include<bits/stdc++.h>
using namespace std;
#define int long long

/*
    ============================================================
    Burnside's Lemma - Necklace Counting
    ============================================================

    Problem:
      Count colorings of n positions using k colors, where two colorings
      are considered the same if one can be obtained from the other by
      rotating the necklace.

    Naively there are k^n colorings, but many of them are equivalent under
    rotation.

    Burnside's Lemma says:

        #orbits = (1 / |G|) * sum_{g in G} Fix(g)

    For a necklace, the group G consists of the n rotations.

    If we rotate by i positions, the positions split into gcd(i,n) cycles.
    A coloring is unchanged by that rotation iff every position in the same
    cycle has the same color.

    Therefore:

        Fix(rotation i) = k ^ gcd(i,n)

    and the answer is:

        (1/n) * sum_{i=1..n} k^gcd(i,n)

    This template handles rotations only. A bracelet (rotations + reflections)
    needs the dihedral group and additional reflection cases.
*/

const int mod = 1e9 + 7;

// Fast modular exponentiation: Base^Power mod MOD.
// Used here to compute k^gcd(i,n), and also the modular inverse of n.
int exp(int Base, int Power) {
    int Result = 1;

    while (Power) {
        if (Power & 1)
            Result = (Result * Base) % mod;

        Base = (Base * Base) % mod;
        Power >>= 1;
    }

    return Result;
}

signed main() {
    int n, k;
    cin >> n >> k;

    int res = 0;

    // Enumerate all n rotations.
    // For rotation i, there are gcd(i,n) independent cycles, and each cycle
    // can choose any of k colors.
    for (int i = 1; i <= n; ++i)
        res = (res + exp(k, gcd(i, n))) % mod;

    // Divide by n modulo MOD.
    // Since MOD is prime and n is assumed not divisible by MOD:
    //     n^(-1) = n^(MOD-2) mod MOD
    res = res * exp(n, mod - 2) % mod;

    cout << res;
}
