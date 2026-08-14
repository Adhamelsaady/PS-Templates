/*
 * XOR OR AND Convolution with FWHT
 *
 * What this file does:
 * Multiplies polynomials / computes convolution in O(N log N).
 *
 * Typical problem to recognize:
 * Convolution combines all pairs with the same index sum: c[k]=sum a[i]b[k-i].
 *
 * Complexity / constraints:
 * Use when O(N^2) pair counting is too slow.
 *
 * Main variables:
 * a,b = input coefficient arrays; fa/fb = transformed arrays; n = transform size; w/root = roots of unity.
 *
 * Variable guide for names used in this implementation:
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * inv: modular inverses.
 * f: function/table array.
 * i: loop index.
 * j: nested loop index.
 * x: unknown or current value.
 * y: unknown or current value.
 * c: third coefficient/constant.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

// Function: add(int a, int b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int add(int a, int b) {
    return (a + b);
}

// Function: sub(int a, int b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
int sub(int a, int b) {
    return (a - b);
}

// Function: fwht(vector<int> &a, int inv, int f).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void fwht(vector<int> &a, int inv, int f) {
    int sz = a.size();
    for (int len = 1; 2 * len <= sz; len <<= 1) {
        for (int i = 0; i < sz; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int x = a[i + j];
                int y = a[i + j + len];

                if (f == 0) {
                    if (!inv)  a[i + j] = y, a[i + j + len] = add(x,  y);
                    else  a[i + j] = sub(y, x), a[i + j + len] = x;
                }
                else if (f == 1) {
                    if (!inv)  a[i + j + len] = add(x, y);
                    else  a[i + j + len] = sub(y, x);
                }
                else {
                    a[i + j] = add(x, y);
                    a[i + j + len] = sub(x, y);
                }
            }
        }
    }
}
// for example to get all pairs xor send a and b as the frequency array of values
vector<int> mul(vector<int> a, vector<int> b, int f) { // 0:AND, 1:OR, 2:XOR
    int sz = a.size();
    fwht(a, 0, f);  fwht(b, 0, f);
    vector<int> c(sz);
    for (int i = 0; i < sz; ++i) {
        c[i] = a[i] * b[i];
    }
    fwht(c, 1, f);
    if (f == 2) {
        for (int i = 0; i < sz; ++i) {
            c[i] = c[i] / sz;
        }
    }
    return c;
}
