int MEX(vector <int> &v) {
    int n = v.size();
    bool exists[n];
    memset(exists, 0, sizeof exists);
    for (auto element: v)
        if (element < n)
            exists[element] = true;
    for (int i = 0; i < n; ++i)
        if (!exists[i])
            return i;
    return n;
}