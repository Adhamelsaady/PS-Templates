#include <bits/stdc++.h>
using namespace std;
#define int long long

/*
    Möbius Function:

        mu(1) = 1

        mu(n) = 0   if n contains a squared prime factor
        mu(n) = 1   if n is a product of an even number of distinct primes
        mu(n) = -1  if n is a product of an odd number of distinct primes

    Examples:
        mu(1)  = 1
        mu(2)  = -1
        mu(6)  = 1   (2 * 3)
        mu(12) = 0   (2^2 * 3)
        mu(30) = -1  (2 * 3 * 5)

    Useful identity:
        sum_{d | n} mu(d) = 1 if n = 1, otherwise 0.

    This version computes mu(1..n) in O(n) using a linear sieve.
*/

vector<int> mobius(int n) {
    vector<int> mu(n + 1);
    vector<int> lp(n + 1);
    vector<int> primes;

    mu[1] = 1;

    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
            mu[i] = -1;
        }

        for (int p : primes) {
            if (1LL * i * p > n) break;

            lp[i * p] = p;

            if (p == lp[i]) {
                // p^2 divides i*p -> Mobius is zero.
                mu[i * p] = 0;
                break;
            } else {
                // p is a new distinct prime factor -> flip the sign.
                mu[i * p] = -mu[i];
            }
        }
    }

    return mu;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    auto mu = mobius(n);

    for (int i = 1; i <= n; ++i)
        cout << "mu(" << i << ") = " << mu[i] << '\n';

    return 0;
}
