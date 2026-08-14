// Fibonacci with fast doubling
// Problem: Compute F(n) modulo mod in O(log n). The recursion returns both F(n) and F(n+1), enabling the doubling identities.
// Use: Call `fib(n,mod)`. Example: `fib(10,1e9+7)=55`.
// Variables: Key variables: n=index; mod=modulus; a=F(k); b=F(k+1); c=F(2k); d=F(2k+1); p=recursive pair.
// Idea: Identities: F(2k)=F(k)(2F(k+1)-F(k)); F(2k+1)=F(k)^2+F(k+1)^2.
// Complexity: Complexity: O(log n) time and O(log n) recursion depth.

pair<ll, ll> fib_fast_doubling(ll n, ll mod) {
    if(n == 0)
        return {0, 1};
    auto p = fib_fast_doubling(n >> 1, mod);
    ll a = p.first;
    ll b = p.second;
    ll c = (a * ((2 * b + mod - a) % mod)) % mod;
    ll d = ((a * a) % mod + (b * b) % mod) % mod;
    if(n & 1)
        return {d, (c + d) % mod};
    else
        return {c, d};
}

ll fib(ll n, ll mod) {
    return fib_fast_doubling(n, mod).first;
}