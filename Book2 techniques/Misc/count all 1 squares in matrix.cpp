// Count all-ones square submatrices
// Problem: Count every square submatrix containing only 1s.
// Use: Call `countSquares(matrix)`. `dp[j]` represents the largest all-ones square ending at the current cell in column j.
// Variables: Key variables: row/col=dimensions; result=number of squares; dp=compressed DP row; prev=old diagonal DP value; temp=saved old dp[j].
// Idea: Transition: if cell is 1, dp = 1 + min(top,left,diagonal); otherwise dp=0. The value dp itself counts how many all-ones squares end at that cell.
// Complexity: Complexity: O(R*C) time and O(C) memory.

 int countSquares(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size(), result = 0, prev = 0;
        vector<int> dp(col + 1, 0);

        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= col; j++) {
                if (matrix[i - 1][j - 1] == 1) {
                    int temp = dp[j];
                    dp[j] = 1 + min(prev, min(dp[j - 1], dp[j]));
                    prev = temp;
                    result += dp[j];
                } else {
                    dp[j] = 0;
                }
            }
        }
        return result;
    }