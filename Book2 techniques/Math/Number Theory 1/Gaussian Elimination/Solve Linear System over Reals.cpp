/*
 * Solve Linear System over Reals
 *
 * What this file does:
 * Solves a system of linear equations by eliminating variables column by column.
 *
 * Typical problem to recognize:
 * Gaussian elimination transforms the system into row-echelon form and then back-substitutes.
 *
 * Complexity / constraints:
 * Real version uses floating point; modular version replaces division by modular inverse.
 *
 * Main variables:
 * a/mat = augmented matrix; n = rows/variables; pivot = current pivot row; where = pivot row of each variable.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * rank: lexicographic rank.
 * i: loop index.
 * c: third coefficient/constant.
 * j: nested loop index.
 * sum: running sum.
 * a: main input/base/coefficient.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

const ld eps = 1e-9;

// Function: Gauss(vector<vector<ld> > a, vector<ld> &ans).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int Gauss(vector<vector<ld> > a, vector<ld> &ans) {
    int n = (int) a.size(), m = (int) a[0].size() - 1;
    vector<int> pos(m, -1);
    ld det = 1;
    int rank = 0;
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int mx = row;
        for (int i = row; i < n; i++) if (fabs(a[i][col]) > fabs(a[mx][col])) mx = i;
        if (fabs(a[mx][col]) < eps) {
            det = 0;
            continue;
        }
        for (int i = col; i <= m; i++) swap(a[row][i], a[mx][i]);
        if (row != mx) det = -det;
        det *= a[row][col];
        pos[col] = row;
        for (int i = 0; i < n; i++) {
            if (i != row && fabs(a[i][col]) > eps) {
                ld c = a[i][col] / a[row][col];
                for (int j = col; j <= m; j++) a[i][j] -= a[row][j] * c;
            }
        }
        ++row;
        ++rank;
    }
    ans.assign(m, 0);
    for (int i = 0; i < m; i++) {
        if (pos[i] != -1) ans[i] = a[pos[i]][m] / a[pos[i]][i];
    }
    for (int i = 0; i < n; i++) {
        ld sum = 0;
        for (int j = 0; j < m; j++) sum += ans[j] * a[i][j];
        if (fabs(sum - a[i][m]) > eps) return -1; //no solution
    }
    for (int i = 0; i < m; i++) if (pos[i] == -1) return 2; //infinte solutions
    return 1; //unique solution
}
