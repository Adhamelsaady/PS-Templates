/*
 * Count Derangements
 *
 * What this file does:
 * Counts permutations with no fixed point: nobody stays in their original position.
 *
 * Typical problem to recognize:
 * A derangement is a permutation where p[i] != i for every i.
 *
 * Complexity / constraints:
 * D(n)=(n-1)(D(n-1)+D(n-2)).
 *
 * Main variables:
 * n = number of elements.
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

// Function: derangement(int n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int derangement(int n){
    if(n<=2){
        return n!=1;
    }
    return (n-1)*(derangement(n-1)+ derangement(n-2));
}
