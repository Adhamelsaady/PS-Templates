#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

/*
    Digit DP + Binary Search on the Answer

    For X, count how many times each digit 0..9 appears while writing
    all positive integers from 1 to X.

    The predicate
        maxDigitFrequency(1..X) <= limit
    is monotone, so binary-search the largest valid X.

    Leading zeroes are NOT counted as written digits.

    Complexity:
      O(10 * number_of_digits * log(answer))
*/

struct DigitDP {
    string digits;
    int target;

    struct Result {
        i128 ways;        // number of positive integers represented
        i128 occurrences; // occurrences of target digit
    };

    Result memo[20][2];
    bool seen[20][2];

    Result dfs(int pos, bool tight, bool started) {
        if (pos == (int)digits.size())
            return {started ? 1 : 0, 0};

        if (!tight && seen[pos][started])
            return memo[pos][started];

        int limit = tight ? digits[pos] - '0' : 9;
        Result ans{0, 0};

        for (int d = 0; d <= limit; ++d) {
            bool nextTight = tight && (d == limit);
            bool nextStarted = started || (d != 0);

            Result sub = dfs(pos + 1, nextTight, nextStarted);
            ans.ways += sub.ways;
            ans.occurrences += sub.occurrences;

            if (nextStarted && d == target)
                ans.occurrences += sub.ways;
        }

        if (!tight) {
            seen[pos][started] = true;
            memo[pos][started] = ans;
        }

        return ans;
    }

    i128 countDigit(ll x, int digit) {
        if (x <= 0) return 0;

        digits = to_string(x);
        target = digit;
        memset(seen, 0, sizeof(seen));

        return dfs(0, true, false).occurrences;
    }

    i128 maxDigitFrequency(ll x) {
        i128 answer = 0;
        for (int digit = 0; digit <= 9; ++digit)
            answer = max(answer, countDigit(x, digit));
        return answer;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll limit;
    cin >> limit;

    DigitDP dp;

    ll low = 0;
    ll high = (ll)((i128)9 * limit);
    ll answer = 0;

    while (low <= high) {
        ll mid = low + (high - low) / 2;

        if (dp.maxDigitFrequency(mid) <= (i128)limit) {
            answer = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << answer << '\n';
}
