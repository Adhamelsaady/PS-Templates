/*
 * Count Subrectangles in Grid
 *
 * What this file does:
 * Counts all axis-aligned subrectangles in an n by m grid.
 *
 * Typical problem to recognize:
 * The number of ways to choose two horizontal boundaries is n(n+1)/2, and similarly for columns.
 *
 * Complexity / constraints:
 * Total = n(n+1)m(m+1)/4.
 *
 * Main variables:
 * n,m = grid dimensions; MinX/MaxX/MinY/MaxY = chosen boundary indices when the containment helper is used.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

int n,m;
// Function: AllSubRectangles().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int AllSubRectangles() {
    return (n * (n + 1) / 2) * (m * (m + 1) / 2);
}
// Function: Contain(int MinX , int MaxX , int MinY , int MaxY).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int Contain(int MinX , int MaxX , int MinY , int MaxY){
    return (MinX * (n - MaxX + 1)) * (MinY) * (m - MaxY + 1);
}
