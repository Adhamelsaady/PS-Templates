/*
 * Floor Sum with Powers
 *
 * What this file does:
 * Computes sums involving floor((a*i+b)/m) without iterating over every i.
 *
 * Typical problem to recognize:
 * floor(x) is the greatest integer <= x. Floor-sum algorithms repeatedly swap numerator and modulus to shrink the problem.
 *
 * Complexity / constraints:
 * Usually O(log m) for the standard floor sum.
 *
 * Main variables:
 * n = number of terms; m = denominator/modulus; a,b = linear expression coefficients; ans = sum.
 *
 * Variable guide for names used in this implementation:
 * mod: modulus.
 * N: maximum precomputation size.
 * x: unknown or current value.
 * a: main input/base/coefficient.
 * b: second input/exponent/coefficient.
 * res: accumulated result.
 * p: prime/modulus/parameter depending on function.
 * i: loop index.
 * j: nested loop index.
 * C: binomial table / constant.
 * c: third coefficient/constant.
 * n: main size/index/input value.
 * sum: running sum.
 * power: exponentiation helper/result.
 * m: second size or modulus.
 * k: count/exponent/selected size.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */


const int mod = 1e9 + 7;
const int N = 20;

// Function: Mod(ll x).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll Mod(ll x) {
    return x >= mod ? x - mod : (x < 0 ? x + mod : x);
}

// Function: qpow(ll a, ll b).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
ll qpow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1ll)
            res = res * a % mod;
        b >>= 1ll, a = a * a % mod;
    }
    return res;
}

struct node {
    ll a[N][N];
    node(int p = 0) {
        for (int i = 0; i <= p; i++)
            for (int j = 0; j <= p; j++)
                a[i][j] = 0;
    }
    ll *operator[](const int &i) {
        return a[i];
    }
};

ll C[N][N], S[N][N];

node simgcd(ll a, ll b, ll c, ll n);

// Function: recurse(ll a, ll b, ll c, ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
node recurse(ll a, ll b, ll c, ll n) {
    if (a == 0) {
        node ans = node(10);
        for (int k1 = 0; k1 <= 10; k1++) {
            ll sum = 0, power = n + 1;
            for (int i = 1; i <= k1 + 1; i++, power = power * (n + 1) % mod)
                sum = (sum + power * S[k1][i]) % mod;
            for (int k2 = 0; k1 + k2 <= 10; k2++, sum = sum * (b / c) % mod)
                ans[k1][k2] = sum;
        }
        return ans;
    }

    if (a >= c) {
        node now = recurse(a % c, b, c, n), ans = node(10);
        for (int k1 = 0; k1 <= 10; k1++) {
            for (int k2 = 0; k1 + k2 <= 10; k2++) {
                ll power = 1;
                for (int i = 0; i <= k2; i++, power = power * (a / c) % mod)
                    ans[k1][k2] = (ans[k1][k2] + C[k2][i] * power % mod * now[k1 + i][k2 - i]) % mod;
            }
        }
        return ans;
    }

    if (b >= c) {
        node now = recurse(a, b % c, c, n), ans = node(10);
        for (int k1 = 0; k1 <= 10; k1++) {
            for (int k2 = 0; k1 + k2 <= 10; k2++) {
                ll power = 1;
                for (int i = 0; i <= k2; i++, power = power * (b / c) % mod)
                    ans[k1][k2] = (ans[k1][k2] + C[k2][i] * power % mod * now[k1][k2 - i]) % mod;
            }
        }
        return ans;
    }

    ll m = (a * n + b) / c;
    node now = recurse(c, a + c - b - 1, a, m - 1), ans = node(10);
    for (int k1 = 0; k1 <= 10; k1++) {
        ll sum = 0, power = n + 1;
        for (int i = 1; i <= k1 + 1; i++, power = power * (n + 1) % mod)
            sum = (sum + power * S[k1][i]) % mod;
        for (int k2 = 0; k1 + k2 <= 10; k2++, sum = sum * m % mod) {
            ans[k1][k2] = sum;
            for (int i = 0; i < k2; i++)
                for (int j = 1; j <= k1 + 1; j++)
                    ans[k1][k2] = (ans[k1][k2] - C[k2][i] * S[k1][j] % mod * now[i][j]) % mod;
            ans[k1][k2] = Mod(ans[k1][k2]);
        }
    }

    return ans;
}
//   sum_{x=0}^{n} x ^ k1 * (floor((a*x + b) / c) ^ k2)
//   for all k1 + k2 <= 10

// Function: simgcd(ll a, ll b, ll c, ll n).
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
node simgcd(ll a, ll b, ll c, ll n) {
    return recurse(a, b, c, n);
}

// Function: init().
// Purpose: see the file header for the problem this helper solves; parameter names above are the contract.
void init() {
    C[0][0] = 1;
    for (int i = 1; i <= 10; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = Mod(C[i - 1][j] + C[i - 1][j - 1]);
    }

    for (int i = 0; i <= 10; i++) {
        S[i][i + 1] = 1;
        for (int j = 0; j < i; j++)
            for (int k = 1; k <= j + 1; k++)
                S[i][k] = Mod(S[i][k] - C[i + 1][j] * S[j][k] % mod);

        ll val = qpow(i + 1, mod - 2);
        for (int j = 1; j <= i + 1; j++)
            S[i][j] = S[i][j] * val % mod;
    }
}
