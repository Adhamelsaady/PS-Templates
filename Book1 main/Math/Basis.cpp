/**
 * XOR Linear Basis (Gaussian elimination over GF(2)).
 *
 * Main use cases:
 *  - Maximum/minimum XOR obtainable from a subset.
 *  - Check whether a value belongs to the XOR span.
 *  - K-th XOR value (under the ordering expected by this basis form).
 *  - Merge two XOR bases.
 *  - Apply a bitwise AND mask and rebuild the basis.
 *
 * Complexity: O(LOG * number_of_insertions), where LOG is the number of bits.
 * NOTE: lg=32 means only bits [0..31] are handled. Increase it if needed.
 */
#include <bits/stdc++.h>

using namespace std;
#define int long long
const int lg = 32;

struct Basis {
    int size = 0;
    vector<int> basis;

    Basis() {
        size = 0;
        basis.assign(lg, {});
// Return true if bit `bit` of n is set. Used to inspect a pivot bit.
    };

    bool on(int n, int bit) {
        return n >> bit & 1;
// Insert n into the XOR span using Gaussian elimination over GF(2).
// Returns true only when n is linearly independent from the current basis.
    }

    bool insert(int n) {
        for (int i = lg - 1; ~i; --i) {
            if (!on(n, i))continue;
            if (!basis[i]) {
                basis[i] = n;
                size++;
                return true;
            }
            n ^= basis[i];
        }
        return false;
// Check whether n belongs to the XOR span of the current basis.
    }

    bool can(int n) {
        for (int i = lg - 1; ~i; --i)
            if (basis[i] and on(n, i))
                n ^= basis[i];
        return n == 0;
// Greedily build the largest value obtainable by XORing basis vectors.
    }

    int max_xor() {
        int answer = 0;
        for (int i = lg - 1; ~i; --i) {
            if (!basis[i] or on(answer, i))continue;
            answer ^= basis[i];
        }
        return answer;
// Reduce n as much as possible lexicographically/numerically from high bits.
    }

    int min_xor(int n) {
        for (int i = lg - 1; ~i; --i) {
            if (on(n, i) and basis[i])
                n ^= basis[i];
        }
        return n;
// Return the k-th XOR value under the ordering represented by this basis.
    }

    int Kth(int k) {
        int answer = 0, cnt = size;
        for (int i = lg - 1; ~i; --i) {
            if (!basis[i])continue;
            --cnt;
            if (on(answer, i)) {
                if ((1LL << cnt) >= k)answer ^= basis[i];
                else k -= 1LL << cnt;
            } else if ((1LL << cnt) < k) {
                answer ^= basis[i];
                k -= 1LL << cnt;
            }
        }
        return answer;
// AND every stored vector with x, then rebuild because the pivots may change.
    }

    void andALL(int x) {
        vector<int> new_Biz;
        for (int i = lg - 1; i >= 0; --i) {
            basis[i] = (basis[i] & x);
            if (basis[i]) new_Biz.push_back(basis[i]);
            basis[i] = 0;
        }
        for (int i: new_Biz)
            insert(i);
// Insert every pivot vector from w. `repeat` is true if at least one vector
// was dependent on the current basis.
    }

    bool merge(Basis &w) {
        bool repeat = false;
        for (auto biz: w.basis)
            if (biz and !insert(biz))
                repeat = true;
        return repeat;
    }
};