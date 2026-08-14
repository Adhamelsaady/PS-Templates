// Count numbers with a fixed remainder in [l,r]
// Problem: Count integers x in [l,r] satisfying x % divisor == mod, in O(1). It also handles negative l correctly.
// Use: Call `cnt(l,r,divisor,mod)`. `mod` must be in [0,divisor-1].
// Variables: Key variables: remL=l mod divisor normalized to non-negative; offset=distance from l to the first desired remainder; first=first valid number >= l.
// Idea: The valid numbers form an arithmetic progression: first, first+divisor, first+2*divisor, ... .
// Complexity: Complexity: O(1).

ll cnt(ll l,ll r,ll divisor,ll mod) {
    if (mod < 0 || mod >= divisor)
        return 0;
    ll remL = ((l % divisor) + divisor) % divisor;
    ll offset = (mod - remL + divisor) % divisor;
    ll first = l + offset;

    if (first > r)
        return 0;

    return 1 + (r - first) / divisor;
}