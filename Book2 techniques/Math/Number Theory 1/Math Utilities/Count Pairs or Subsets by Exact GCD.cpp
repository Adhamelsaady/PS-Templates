/*
 * Count Pairs or Subsets by Exact GCD
 *
 * What this file does:
 * Computes the greatest common divisor, including variants for negatives or using only binary operations.
 *
 * Typical problem to recognize:
 * gcd(a,b) is the largest positive integer dividing both numbers.
 *
 * Complexity / constraints:
 * Binary GCD uses shifts/subtraction; Extended Euclid also gives coefficients.
 *
 * Main variables:
 * a,b = input integers; x,y = Bézout coefficients in extended Euclid; g = gcd.
 *
 * Variable guide for names used in this implementation:
 * N: maximum precomputation size.
 * dp: dynamic programming table.
 * n: main size/index/input value.
 * i: loop index.
 * j: nested loop index.
 * a: main input/base/coefficient.
 *
 * How to use:
 * 1) Copy the needed function(s) into your template.
 * 2) Match the parameter order with the function signature below.
 * 3) Check the modulus / indexing assumptions before using it.
 * 4) Keep the helper functions it depends on.
 */

const int N = 1e6 + 10;
int freq[N], cnt[N];
ll dp[N];
int main() {
    PRE();
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            cnt[i] += freq[j];
        }
    }
    for (int i = N - 1; i > 0; i--) {
        ll total = 1LL * cnt[i] * (cnt[i] - 1) / 2; // number of pairs with gcd i , if subsets you can make it 2 ^ cnt[i] - 1
        for (int j = 2 * i; j < N; j += i) {
            total -= dp[j];
        }
        dp[i] = total;
    }

    cout << dp[1] << "\n";
}
