// Dynamic sum of the k smallest values
// Problem: Maintain an array under point updates while being able to keep the sum of its k smallest values. Two multisets split the elements into the selected k smallest (`x`) and the rest (`y`).
// Use: Initialize `a`, `n`, and `k`; put all values into `y`; call `balance()` after initialization/updates. `sum` is the current sum of the k smallest values.
// Variables: Key variables: x=multiset containing the k smallest values; y=remaining values; a=array; k=number selected; sum=sum of x; v1=largest selected candidate; v2=smallest unselected candidate; old/nw=updated value.
// Idea: Invariant: every value in x <= every value in y, and |x|=k.
// Complexity: Complexity: O(log n) per insertion/deletion plus balancing swaps; each element crosses the boundary only when needed.

const int N = 5e5 + 10;
int n , k , q;
multiset<ll> x , y;
ll a[N];
ll sum = 0;
void balance() {
    while (x.size() < k) {
        sum += *y.rbegin();
        x.insert(*y.rbegin());
        y.erase(y.find(*y.rbegin()));
    }
    if (x.empty() || y.empty()) return;
    while (1) {
        auto it = x.begin();
        auto iit = y.rbegin();
        if (*it >= *iit) return;
        ll v1 = *it , v2 = *iit;
        sum -= v1 , sum += v2;
        x.erase(it);
        y.erase(y.find(*y.rbegin()));
        x.insert(v2) , y.insert(v1);
    }
}
void erase(ll old) {
    auto it = x.find(old);
    if (it != x.end()) {
        sum -= old;
        x.erase(it);
    }else {
        y.erase(y.find(old));
    }
    balance();
}
void insert(ll nw) {
    y.insert(nw);
    balance();
}