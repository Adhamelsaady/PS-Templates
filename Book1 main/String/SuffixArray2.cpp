#include <bits/stdc++.h>
using namespace std;

struct SuffixArray {
    // suff is the suffix array with the empty suffix being suff[0]
    // lcp[i] holds the lcp between sa[i], sa[i - 1]
    int n;
    vector<int> suff, lcp, pos, lg;
    vector<array<int, 21>> table;

    SuffixArray(string& s, int lim = 256) {
        n = s.size() + 1;
        int k = 0, a, b;
        vector<int> c(s.begin(), s.end() + 1), tmp(n), frq(max(n, lim));
        c.back() = 0;
        suff = lcp = pos = tmp, iota(suff.begin(), suff.end(), 0);
        for (int j = 0, p = 0; p < n; j = max(1ll, j * 2), lim = p) {
            p = j, iota(tmp.begin(), tmp.end(), n - j);
            for (int i = 0; i < n; i++)
                if (suff[i] >= j) tmp[p++] = suff[i] - j;

            fill(frq.begin(), frq.end(), 0);
            for (int i = 0; i < n; i++) frq[c[i]]++;
            for (int i = 1; i < lim; i++) frq[i] += frq[i - 1];
            for (int i = n; i--;) suff[--frq[c[tmp[i]]]] = tmp[i];

            swap(c, tmp), p = 1, c[suff[0]] = 0;
            for (int i = 1; i < n; i++) {
                a = suff[i - 1], b = suff[i];
                c[b] = tmp[a] == tmp[b] && tmp[a + j] == tmp[b + j] ? p - 1 : p++;
            }
        }

        for (int i = 1; i < n; i++) pos[suff[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[pos[i++]] = k)
            for (k && k--, j = suff[pos[i] - 1]; s[i + k] == s[j + k]; k++) {}
    }

    void preLcp() {
        lg.resize(n + 5);
        table.resize(n + 5);
        for (int i = 2; i < n + 5; ++i) lg[i] = lg[i / 2] + 1;
        for (int i = 0; i < n; ++i) table[i][0] = lcp[i];
        for (int j = 1; j <= lg[n]; ++j)
            for (int i = 0; i <= n - (1 << j); ++i)
                table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    // pass the pos of the suffixes
    int queryLcp(int i, int j) {
        if (i == j) return n - suff[i] - 1;
        if (i > j) swap(i, j);
        i++;
        int len = lg[j - i + 1];
        return min(table[i][len], table[j - (1 << len) + 1][len]);
    }
};

namespace SuffixArrayTasks {

    /**
     * Complexity: O(|P| log N) where |P| is pattern length, N is string length.
     * Description: Finds the [L, R) range of indices in the suffix array where all suffixes begin with the given pattern.
     * Example: s = "abracadabra", pattern = "abra"
     *          Returns [1, 3) (corresponding to suffixes "abra" and "abracadabra" in the sorted suffix array).
     */
    pair<int, int> patternRange(string& s, SuffixArray& sa, const string& pattern) {
        int lo = 1, hi = sa.n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (s.compare(sa.suff[mid], pattern.size(), pattern) < 0) lo = mid + 1;
            else hi = mid;
        }
        int L = lo;
        lo = 1; hi = sa.n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (s.compare(sa.suff[mid], pattern.size(), pattern) <= 0) lo = mid + 1;
            else hi = mid;
        }
        int R = lo;
        return {L, R};
    }

    /**
     * Complexity: O(|P| log N)
     * Description: Checks if a given pattern exists anywhere in the text as a contiguous substring.
     * Example: s = "abracadabra", pattern = "cad" -> Returns true.
     */
    bool patternExists(string& s, SuffixArray& sa, const string& pattern) {
        auto [L, R] = patternRange(s, sa, pattern);
        return L < R;
    }

    /**
     * Complexity: O(|P| log N)
     * Description: Returns the exact number of times a pattern appears as a contiguous substring in the text.
     * Example: s = "abracadabra", pattern = "a" -> Returns 5.
     */
    int countPatternOccurrences(string& s, SuffixArray& sa, const string& pattern) {
        auto [L, R] = patternRange(s, sa, pattern);
        return R - L;
    }

    /**
     * Complexity: O(|P| log N + K log K) where K is the number of occurrences.
     * Description: Returns a sorted vector of 0-based indices representing every starting position of the pattern in the string.
     * Example: s = "abracadabra", pattern = "abra" -> Returns [0, 7].
     */
    vector<int> patternPositions(string& s, SuffixArray& sa, const string& pattern) {
        auto [L, R] = patternRange(s, sa, pattern);
        vector<int> ans;
        for (int i = L; i < R; ++i) ans.push_back(sa.suff[i]);
        sort(ans.begin(), ans.end());
        return ans;
    }

    /**
     * Complexity: O(N)
     * Description: Counts the total number of mathematically unique substrings that can be formed from the string.
     * Example: s = "abab" -> Substrings: "a", "b", "ab", "ba", "aba", "bab", "abab" -> Returns 7.
     */
    long long countDistinctSubstrings(string& s, SuffixArray& sa) {
        long long ans = 0;
        for (int i = 1; i < sa.n; ++i) {
            long long suffixLength = (int)s.size() - sa.suff[i];
            ans += suffixLength - sa.lcp[i];
        }
        return ans;
    }

    /**
     * Complexity: O(N)
     * Description: Finds the longest substring that appears at least twice in the text. The occurrences are allowed to overlap.
     * Example: s = "banana" -> Returns "ana" (appears at index 1 and 3).
     */
    string longestRepeatedSubstring(string& s, SuffixArray& sa) {
        int bestLength = 0, bestStart = -1;
        for (int i = 1; i < sa.n; ++i) {
            if (sa.lcp[i] > bestLength) {
                bestLength = sa.lcp[i];
                bestStart = sa.suff[i];
            }
        }
        if (bestLength == 0) return "";
        return s.substr(bestStart, bestLength);
    }

    /**
     * Complexity: O(N) (Requires sa.preLcp() to be called first)
     * Description: Finds the longest substring that appears at least K times in the text.
     * Example: s = "abracadabra", k = 2 -> Returns "abra".
     */
    string longestSubstringAtLeastK(string& s, SuffixArray& sa, int k) {
        int m = s.size();
        if (k <= 1) return s;
        if (k > m) return "";
        int bestLength = 0, bestStart = -1;
        for (int L = 1; L + k - 1 < sa.n; ++L) {
            int R = L + k - 1;
            int current = sa.queryLcp(L, R);
            if (current > bestLength) {
                bestLength = current;
                bestStart = sa.suff[L];
            }
        }
        if (bestLength == 0) return "";
        return s.substr(bestStart, bestLength);
    }

    /**
     * Complexity: O(N log N)
     * Description: Finds the longest substring that repeats at least twice, but the occurrences do not overlap.
     * Example: s = "abracadabra" -> Returns "abra" (starts at 0 and 7; they don't overlap). 
     *          (Compare to "banana" -> longest non-overlapping is "an" or "na", since "ana" overlaps itself).
     */
    string longestNonOverlappingRepeat(string& s, SuffixArray& sa) {
        int m = s.size();
        auto can = [&](int len, int& answerStart) {
            for (int i = 1; i < sa.n;) {
                int mn = sa.suff[i], mx = sa.suff[i], j = i + 1;
                while (j < sa.n && sa.lcp[j] >= len) {
                    mn = min(mn, sa.suff[j]);
                    mx = max(mx, sa.suff[j]);
                    if (mx - mn >= len) {
                        answerStart = mn;
                        return true;
                    }
                    ++j;
                }
                i = j;
            }
            return false;
        };
        int lo = 1, hi = m / 2, bestLength = 0, bestStart = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2, start = -1;
            if (can(mid, start)) {
                bestLength = mid;
                bestStart = start;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (bestLength == 0) return "";
        can(bestLength, bestStart);
        return s.substr(bestStart, bestLength);
    }

    // Helper: Finds a character that doesn't exist in either string to use as a delimiter.
    char getSeparator(const string& a, const string& b = "") {
        vector<bool> used(256);
        for (unsigned char c : a) used[c] = true;
        for (unsigned char c : b) used[c] = true;
        for (int c = 1; c < 256; ++c) {
            if (!used[c]) return (char)c;
        }
        return '#';
    }

    /**
     * Complexity: O(|A| + |B|) after O((|A|+|B|) log(|A|+|B|)) Suffix Array construction.
     * Description: Finds the longest contiguous substring that is common to both string 'A' and string 'B'.
     * Example: a = "zxabcdezy", b = "yzabcdezx" -> Returns "abcdez".
     */
    string longestCommonSubstring(string a, string b) {
        char separator = getSeparator(a, b);
        string t = a + string(1, separator) + b;
        SuffixArray sa(t);
        int n1 = a.size();
        auto owner = [&](int position) {
            if (position < n1) return 0;
            if (position > n1 && position < (int)t.size()) return 1;
            return -1;
        };
        int bestLength = 0, bestStart = -1;
        for (int i = 1; i < sa.n; ++i) {
            int x = sa.suff[i - 1], y = sa.suff[i];
            int ox = owner(x), oy = owner(y);
            if (ox != -1 && oy != -1 && ox != oy) {
                if (sa.lcp[i] > bestLength) {
                    bestLength = sa.lcp[i];
                    bestStart = (ox == 0) ? x : y;
                }
            }
        }
        if (bestLength == 0) return "";
        return t.substr(bestStart, bestLength);
    }

    /**
     * Complexity: O(N)
     * Description: Returns the K-th string if you were to extract every distinct substring and sort them alphabetically.
     * Example: s = "aba". Distinct sorted: "a", "ab", "aba", "b", "ba". k = 4 -> Returns "b".
     */
    string kthDistinctSubstring(string& s, SuffixArray& sa, long long k) {
        int m = s.size();
        for (int i = 1; i < sa.n; ++i) {
            long long suffixLength = m - sa.suff[i];
            long long newSubstrings = suffixLength - sa.lcp[i];
            if (k > newSubstrings) {
                k -= newSubstrings;
            } else {
                int len = sa.lcp[i] + k;
                return s.substr(sa.suff[i], len);
            }
        }
        return ""; // k > number of distinct substrings
    }

    /**
     * Complexity: O(N)
     * Description: Returns an array where ans[L] contains the number of distinct substrings of exact length L.
     * Example: s = "aba" -> lengths of 1: ("a", "b") = 2. lengths of 2: ("ab", "ba") = 2. lengths of 3: ("aba") = 1.
     *          Returns [0, 2, 2, 1].
     */
    vector<long long> distinctSubstringsByLength(string& s, SuffixArray& sa) {
        int m = s.size();
        vector<long long> diff(m + 2), answer(m + 1);
        for (int i = 1; i < sa.n; ++i) {
            int L = sa.lcp[i] + 1;
            int R = m - sa.suff[i];
            if (L <= R) {
                diff[L]++;
                diff[R + 1]--;
            }
        }
        long long current = 0;
        for (int len = 1; len <= m; ++len) {
            current += diff[len];
            answer[len] = current;
        }
        return answer;
    }

    /**
     * Complexity: O(1) (Requires sa.preLcp() to be called first)
     * Description: Quickly determines lexicographical order between any two specific substrings s[l1...r1] and s[l2...r2].
     *              Returns -1 if first < second, 0 if equal, 1 if first > second.
     * Example: s = "banana", l1=1, r1=3 ("ana"), l2=3, r2=5 ("ana") -> Returns 0.
     */
    int compareSubstrings(string& s, SuffixArray& sa, int l1, int r1, int l2, int r2) {
        int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
        int common = sa.queryLcp(sa.pos[l1], sa.pos[l2]);
        common = min({common, len1, len2});
        if (common == min(len1, len2)) {
            if (len1 == len2) return 0;
            return len1 < len2 ? -1 : 1;
        }
        if (s[l1 + common] < s[l2 + common]) return -1;
        return 1;
    }

    /**
     * Complexity: O(log N) per query (Requires sa.preLcp() to be called first)
     * Description: Rapidly counts how many times the substring s[l...r] appears in the whole string s. Useful for Q queries.
     * Example: s = "abracadabra", query l=0, r=3 ("abra") -> Returns 2.
     */
    int countSubstringOccurrences(string& s, SuffixArray& sa, int l, int r) {
        int len = r - l + 1, p = sa.pos[l];
        int lo = 1, hi = p;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (sa.queryLcp(mid, p) >= len) hi = mid;
            else lo = mid + 1;
        }
        int L = lo;
        lo = p, hi = sa.n - 1;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (sa.queryLcp(p, mid) >= len) lo = mid;
            else hi = mid - 1;
        }
        int R = lo;
        return R - L + 1;
    }

    /**
     * Complexity: O(N)
     * Description: Finds the lexicographically smallest string that can be made by shifting the string cyclically.
     * Example: s = "cba" -> shifts are "cba", "bac", "acb". "acb" is smallest -> Returns "acb".
     */
    string minimumRotation(string s) {
        if (s.empty()) return "";
        int m = s.size();
        string t = s + s;
        SuffixArray sa(t);
        for (int rank = 1; rank < sa.n; ++rank) {
            int start = sa.suff[rank];
            if (start < m) return t.substr(start, m);
        }
        return "";
    }

    /**
     * Complexity: O(N)
     * Description: Counts the number of unique strings you can make by shifting the string cyclically.
     * Example: s = "abab" -> shifts: "abab", "baba", "abab", "baba". Only 2 distinct. -> Returns 2.
     */
    int countDistinctRotations(string s) {
        if (s.empty()) return 0;
        int m = s.size();
        string t = s + s;
        SuffixArray sa(t);
        sa.preLcp();
        int answer = 0, previousRank = -1;
        for (int rank = 1; rank < sa.n; ++rank) {
            int start = sa.suff[rank];
            if (start >= m) continue;
            if (previousRank == -1) {
                answer++;
            } else {
                int common = sa.queryLcp(previousRank, rank);
                if (common < m) answer++;
            }
            previousRank = rank;
        }
        return answer;
    }

    /**
     * Complexity: O(N) (Requires sa.preLcp() to be called first)
     * Description: Finds the longest contiguous substring that reads the same forwards and backwards.
     * Example: s = "babad" -> Returns "bab" (or "aba").
     */
    string longestPalindromeSA(string s) {
        if (s.empty()) return "";
        int m = s.size();
        string rev = s;
        reverse(rev.begin(), rev.end());
        char separator = getSeparator(s, rev);
        string t = s + string(1, separator) + rev;
        SuffixArray sa(t);
        sa.preLcp();
        int bestLength = 1, bestStart = 0;
        
        for (int center = 0; center < m; ++center) { // Odd lengths
            int originalPosition = center;
            int reversePosition = m + 1 + (m - 1 - center);
            int radius = sa.queryLcp(sa.pos[originalPosition], sa.pos[reversePosition]);
            int length = 2 * radius - 1;
            if (length > bestLength) {
                bestLength = length;
                bestStart = center - radius + 1;
            }
        }
        for (int center = 1; center < m; ++center) { // Even lengths
            int originalPosition = center;
            int reversePosition = m + 1 + (m - center);
            int radius = sa.queryLcp(sa.pos[originalPosition], sa.pos[reversePosition]);
            int length = 2 * radius;
            if (length > bestLength) {
                bestLength = length;
                bestStart = center - radius;
            }
        }
        return s.substr(bestStart, bestLength);
    }

    /**
     * Complexity: O(N)
     * Description: Finds the exact substring of length K that appears the highest number of times in the text.
     * Example: s = "ababa", k = 2 -> Returns {2, "ab"} (frequency 2, string "ab").
     */
    pair<int, string> mostFrequentFixedLength(string& s, SuffixArray& sa, int k) {
        int m = s.size();
        if (k <= 0 || k > m) return {0, ""};
        int bestFrequency = 0, bestRank = -1, currentFrequency = 0;
        for (int i = 1; i < sa.n; ++i) {
            int suffixLength = m - sa.suff[i];
            if (suffixLength < k) {
                currentFrequency = 0;
                continue;
            }
            if (i > 1 && sa.lcp[i] >= k) {
                currentFrequency++;
            } else {
                currentFrequency = 1;
            }
            if (currentFrequency > bestFrequency) {
                bestFrequency = currentFrequency;
                bestRank = i;
            }
        }
        if (bestRank == -1) return {0, ""};
        return {bestFrequency, s.substr(sa.suff[bestRank], k)};
    }

    /**
     * Complexity: O(N log N) (Requires sa.preLcp() to be called first)
     * Description: For each index i, finds the longest prefix of s[i...] that already appeared at some starting index j < i.
     *              Useful for LZ77 compression logic.
     * Example: s = "abacaba" -> At i=4 ("aba"), it previously appeared at i=0. Thus, ans[4] = 3.
     */
    vector<int> longestPreviousFactor(string& s, SuffixArray& sa) {
        int m = s.size();
        vector<int> lpf(m);
        set<int> previousRanks;
        for (int i = 0; i < m; ++i) {
            int rank = sa.pos[i], best = 0;
            auto it = previousRanks.lower_bound(rank);
            if (it != previousRanks.end()) {
                best = max(best, sa.queryLcp(rank, *it));
            }
            if (it != previousRanks.begin()) {
                --it;
                best = max(best, sa.queryLcp(rank, *it));
            }
            lpf[i] = best;
            previousRanks.insert(rank);
        }
        return lpf;
    }

    /**
     * Complexity: O(1) (Requires sa.preLcp() to be called first)
     * Description: Direct query for the length of the Longest Common Prefix between the suffix starting at 'i' and suffix starting at 'j'.
     * Example: s = "banana", i = 1 ("anana"), j = 3 ("ana") -> Returns 3.
     */
    int lcpOfSuffixPositions(SuffixArray& sa, int i, int j) {
        return sa.queryLcp(sa.pos[i], sa.pos[j]);
    }
}