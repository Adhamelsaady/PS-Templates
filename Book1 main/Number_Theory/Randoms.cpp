vector <int> PrimeFact;
void PrimeFactorization(int n) {
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            PrimeFact.push_back(i);
            n /= i;
        }
    }
    if (n > 1)
        PrimeFact.push_back(n);
}

vector<int> divisors;
void getDivisors(int n) {
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i * i != n) {
                divisors.push_back(n / i);
            }
        }
    }
}

vector<int> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > n) {
                break;
            }
            is_prime[i * p] = false;
            if (i % p == 0) {
                break;
            }
        }
    }
    return primes;
}

vector<int> prime_factorization(int n, vector<int>& primes) {
    vector<int> ret;
    for (int i = 0; i < (int)primes.size(); ++i) {
        if (primes[i] * primes[i] > n) {
            break;
        }
        while (n % primes[i] == 0) {
            n /= primes[i];
            ret.push_back(primes[i]);
        }
    }
    if (n != 1) {
        ret.push_back(n);
    }
    return ret;
}

int fast_power(int n , int p , int mod){
    int res = 1;
    while(p){
        if(p & 1) {
            res = (res * n) % mod;
            p--;
        } else {
            n = (n % mod) * (n % mod);
            n %= mod;
            p /= 2;
        }
    }
    return res;
}


vector<int> primes, low;

void Sieve(int n) {
    low.assign(n + 1, 0);

    for (int i = 2; i <= n; ++i) {
        if (!low[i]) {
            low[i] = i;
            primes.push_back(i);
        }

        for (int &j: primes) {
            if (j > low[i] || i * j > n) break;
            low[j * i] = j;
        }
    }
}