#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    SWAG (Sliding Window Aggregation) using Two Stacks

    Supports a queue with:
      push_back(x)
      pop_front()
      aggregate() over the whole queue

    Requires only an associative merge operation.

    Here merge = bitwise OR.

    Each element moves between stacks at most once:
      amortized O(1) per operation.

    This template also works for many associative operations
    such as min, max, gcd, sum, bitwise AND/OR, etc.
*/

template<class T, class Merge>
class SWAG {
    struct Node {
        T value;
        T aggregate;
    };

    vector<Node> in, out;
    Merge merge;

    void moveInToOut() {
        while (!in.empty()) {
            T x = in.back().value;
            in.pop_back();

            T agg = out.empty() ? x : merge(x, out.back().aggregate);
            out.push_back({x, agg});
        }
    }

public:
    explicit SWAG(Merge merge = Merge()) : merge(merge) {}

    void push(T x) {
        T agg = in.empty() ? x : merge(in.back().aggregate, x);
        in.push_back({x, agg});
    }

    void pop() {
        if (out.empty())
            moveInToOut();
        out.pop_back();
    }

    T aggregate() const {
        if (out.empty()) return in.back().aggregate;
        if (in.empty())  return out.back().aggregate;
        return merge(out.back().aggregate, in.back().aggregate);
    }

    int size() const {
        return (int)in.size() + (int)out.size();
    }
};

struct BitwiseOr {
    ll operator()(ll a, ll b) const {
        return a | b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    ll x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;

    SWAG<ll, BitwiseOr> window;

    ll answer = 0;
    ll current = x;

    for (int i = 0; i < n; ++i) {
        if (i > 0)
            current = (current * a + b) % c;

        window.push(current);

        if (window.size() == k) {
            answer ^= window.aggregate();
            window.pop();
        }
    }

    cout << answer << '\n';
}
