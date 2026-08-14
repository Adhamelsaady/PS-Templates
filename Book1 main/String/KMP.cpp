
vector <int> kmp(string &s) {
    int n = s.size();
    vector <int> pi(n);
    for (int i = 1 , j = 0; i < n; i++) {
        while (j && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}


vector <vector<int>> compute_automaton(string s) {
    s += '#';
    int n = s.size();
    vector<int> pi = kmp(s);
    vector <vector<int>> aut (n, vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }

    return aut;
}