#include <bits/stdc++.h>
using namespace std;

/*
    Lexicographically Smallest Permutation with Local Adjacency Constraint

    Construct a permutation of 1..n such that:
        |p[i] - p[i+1]| != 1

    Strategy:
      1) Greedily take the smallest currently valid value while
         more than 6 values remain.
      2) Brute-force the final at-most-6 values and choose the
         lexicographically smallest valid suffix.

    The tiny brute-force suffix protects the greedy construction
    from end-game conflicts.

    Complexity:
      O(n log n + 6!)
*/

static bool validSuffix(int previous, const vector<int>& suffix) {
    for (int x : suffix) {
        if (abs(previous - x) == 1)
            return false;
        previous = x;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    set<int> remaining;
    for (int x = 1; x <= n; ++x)
        remaining.insert(x);

    vector<int> answer;
    answer.reserve(n);

    int previous = -1000000000;

    while ((int)remaining.size() > 6) {
        auto it = remaining.begin();

        while (it != remaining.end() && abs(previous - *it) == 1)
            ++it;

        if (it == remaining.end()) {
            cout << "NO SOLUTION\n";
            return 0;
        }

        previous = *it;
        answer.push_back(*it);
        remaining.erase(it);
    }

    vector<int> tail(remaining.begin(), remaining.end());
    vector<int> bestTail;
    bool found = false;

    do {
        if (validSuffix(previous, tail)) {
            bestTail = tail; // permutations are generated lexicographically
            found = true;
            break;
        }
    } while (next_permutation(tail.begin(), tail.end()));

    if (!found) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    answer.insert(answer.end(), bestTail.begin(), bestTail.end());

    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
}
