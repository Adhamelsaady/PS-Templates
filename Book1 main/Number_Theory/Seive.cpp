vector <int> primes;
vector<bool> IsPrime; // Don't forget to resize it to N
void sieve(int n) {
    IsPrime[0] = IsPrime[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (IsPrime[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > n) {
                break;
            }
            IsPrime[i * p] = false;
            if (i % p == 0) {
                break;
            }
        }
    }
}


const int N = 1e7 + 6;
bool is_prime[N];
void sieve() {  // O(N) ~= O(N*log(log(N)))
  fill(is_prime, is_prime + N, true);
  is_prime[0] = is_prime[1] = false;

  for (int p = 2; p * p < N; p++) {
    if (is_prime[p]) {
      for (int m = p * p; m < N; m += p) {
        is_prime[m] = false;
      }
    }
  }
}



void build() {
    for (int i = 0; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++)
        if (spf[i] == i)
            for (int j = i * i; j < N; j += i)
                if (spf[j] == j) spf[j] = i;

}