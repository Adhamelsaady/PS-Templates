#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
    Maximum Empty Rectangle in a Binary/Grid Matrix

    For each row:
      - convert consecutive empty cells above it into histogram heights
      - solve Largest Rectangle in Histogram with a monotonic stack

    Grid convention here:
      '.' = empty
      '*' = blocked

    Complexity: O(n * m)
*/

ll largestRectangle(const vector<int>& height) {
    int m = (int)height.size();
    vector<int> st;
    st.reserve(m);

    ll best = 0;

    for (int i = 0; i <= m; ++i) {
        int current = (i == m ? 0 : height[i]);

        while (!st.empty() && height[st.back()] >= current) {
            int h = height[st.back()];
            st.pop_back();

            int left = st.empty() ? 0 : st.back() + 1;
            int width = i - left;

            best = max(best, 1LL * h * width);
        }

        if (i < m)
            st.push_back(i);
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> height(m, 0);
    ll answer = 0;

    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;

        for (int j = 0; j < m; ++j) {
            if (row[j] == '.')
                ++height[j];
            else
                height[j] = 0;
        }

        answer = max(answer, largestRectangle(height));
    }

    cout << answer << '\n';
}
