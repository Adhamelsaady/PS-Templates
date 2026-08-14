// Largest all-ones rectangle in a binary matrix
// Problem: Find the maximum-area rectangle consisting only of 1s. Each row is treated as the base of a histogram and solved with a monotonic stack.
// Use: Call `BiggestRec(matrix)` with a non-empty binary matrix. `calc(heights)` can also be reused for a single histogram.
// Variables: Key variables: matrix=input grid; hist[j]=consecutive 1s ending at the current row in column j; heights=histogram heights; stack=indices with increasing heights; m=height of a popped bar; v=its maximum valid width; result=best area.
// Idea: Terminology: a monotonic stack keeps indices ordered by their height; it lets us find the maximal width for every histogram bar in linear time.
// Complexity: Complexity: O(R*C) time and O(C) extra memory.

int calc(const vector<int>& heights) {
    int result = 0;
    stack<int> stack;

    for (int i = 0; i <= heights.size(); ++i) {
        while (!stack.empty() && (i == heights.size() || heights[stack.top()] > heights[i])) {
            const int m = heights[stack.top()];
            stack.pop();
            const int v = stack.empty() ? i : i - stack.top() - 1;
            result = max(result, m * v);
        }
        stack.push(i);
    }

    return result;
}
int BiggestRec(vector<vector<int>>& matrix) {
    if (matrix.empty())
        return 0;

    int result = 0;
    vector<int> hist(matrix[0].size());

    for (auto &row: matrix) {
        for (int i = 0; i < row.size(); ++i)
            hist[i] = row[i] == 0 ? 0 : hist[i] + 1;
        result = max(result, calc(hist));
    }
    return result;
}
