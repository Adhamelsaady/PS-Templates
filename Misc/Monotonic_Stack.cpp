vector<int> prevGreater(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] <= a[i]) st.pop();
        res[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return res;
}

vector<int> nextGreater(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] < a[i]) st.pop();
        res[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return res;
}

vector<int> prevSmaller(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        res[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return res;
}

vector<int> nextSmaller(const vector<int>& a) {
    int n = a.size();
    vector<int> res(n, n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.top()] > a[i]) st.pop();
        res[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    return res;
}
