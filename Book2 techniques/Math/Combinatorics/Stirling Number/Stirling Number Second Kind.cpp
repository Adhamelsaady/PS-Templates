/*
 * Stirling Number Second Kind
 *
 * What this file does:
 * Computes Stirling numbers. Second-kind S(n,k) counts partitions of n distinct elements into k nonempty unlabeled groups. First-kind variants count permutations by cycles.
 *
 * Typical problem to recognize:
 * A set partition is a split into nonempty groups where group order does not matter.
 *
 * Complexity / constraints:
 * Use the exact first/second-kind file according to the problem.
 *
 * Main variables:
 * n = number of elements; k = number of groups/cycles.
 *
 * Variable guide for names used in this implementation:
 * n: main size/index/input value.
 * k: count/exponent/selected size.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: stirling_number(int n,int k).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int stirling_number(int n,int k){
    if(k==0)return n==0;
    if(n==0)return 0;
    return stirling_number(n-1,k-1)+(n-1)* stirling_number(n-1,k);
    //S[i][j]=S[i-1][j-1]+s[i-1][j]*(i-1)
    //S(n,k) as the different ways to cut n different elements into k undifferentiated non-empty subsets. For example, S(5,3) denotes to:25
}
