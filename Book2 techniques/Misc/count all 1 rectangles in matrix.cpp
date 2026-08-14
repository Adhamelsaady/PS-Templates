// Count all-ones submatrices
// Problem: Count every rectangular submatrix consisting entirely of 1s. Each row becomes a histogram, then a monotonic stack counts rectangles ending at that row.
// Use: Call `numSubmat(mat)`.
// Variables: Key variables: heights[j]=consecutive ones ending at current row; st=monotonic stack; h=current bar height; j=previous smaller-bar boundary; prev=number of rectangles contributed before current bar; cur=number contributed by rectangles ending at current column; res=total.
// Idea: Terminology: unlike the square problem, a submatrix may have any height and width.
// Complexity: Complexity: O(R*C) time and O(C) auxiliary memory.

int numSubmat(vector<vector<int>>& mat) {
        int n = mat[0].size();
        vector<int> heights(n, 0);
        int res = 0;
        for (const auto& row : mat) {
            for (int i = 0; i < n; ++i) {
                heights[i] = (row[i] == 0) ? 0 : heights[i] + 1;
            }
            stack<vector<int>> st;
            st.push({-1, 0, -1});
            for (int i = 0; i < n; ++i) {
                int h = heights[i];
                while (st.top()[2] >= h) {
                    st.pop();
                }
                auto& top = st.top();
                int j = top[0];
                int prev = top[1];
                int cur = prev + (i - j) * h;
                st.push({i, cur, h});
                res += cur;
            }
        }
        return res;
}