vector<int> computePrefix(string &s) {
    vector<int> longestPrefix(s.size());
    for (int i = 1; i < s.size(); ++i) {
        int k = longestPrefix[i - 1];
        while (k and s[k] != s[i])
            k = longestPrefix[k - 1];
 
        k += s[k] == s[i];
        longestPrefix[i] = k;
    }
    return longestPrefix;
}
 
bool inside(string &pat, string &s, vector<int> &pi) {
    int k = 0;
    for (int i = 0; i < s.size(); ++i) {
        while (k and pat[k] != s[i])
            k = pi[k - 1];
 
        k += pat[k] == s[i];
        if (k == pat.size())
            return true;
    }
    return false;
}
 
int maxMatching_Pref_Suff(string &last, string &cur, vector<int> &pi) {
    int k = 0;
    for (int i = 0; i < last.size(); ++i) {
        while (k and cur[k] != last[i])
            k = pi[k - 1];
 
        k += cur[k] == last[i];
    }
    return k;
}