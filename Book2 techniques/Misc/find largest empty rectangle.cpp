// Largest all-zero rectangle in a binary matrix
// Problem: Find the maximum-area rectangle containing only zeros. `d[j]` stores the last row containing a 1 in column j, so i-d[j] is the current zero height.
// Use: Call `zero_matrix(a)` on a non-empty binary matrix.
// Variables: Key variables: d[j]=last row with a 1; d1/d2=nearest columns with strictly greater height on the left/right; st=monotonic stack; i=current row; ans=maximum area.
// Idea: This is the zero-version of largest rectangle in a histogram: each row creates heights of consecutive zeros.
// Complexity: Complexity: O(R*C) time and O(C) memory.

int zero_matrix(vector<vector<int>> a) {
    int n = a.size();
    int m = a[0].size();

    int ans = 0;
    vector<int> d(m, -1), d1(m), d2(m);
    stack<int> st;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 1)
                d[j] = i;
        }

        for (int j = 0; j < m; ++j) {
            while (!st.empty() && d[st.top()] <= d[j])
                st.pop();
            d1[j] = st.empty() ? -1 : st.top();
            st.push(j);
        }
        while (!st.empty())
            st.pop();

        for (int j = m - 1; j >= 0; --j) {
            while (!st.empty() && d[st.top()] <= d[j])
                st.pop();
            d2[j] = st.empty() ? m : st.top();
            st.push(j);
        }
        while (!st.empty())
            st.pop();

        for (int j = 0; j < m; ++j)
            ans = max(ans, (i - d[j]) * (d2[j] - d1[j] - 1));
    }
    return ans;
}