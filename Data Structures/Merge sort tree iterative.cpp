const int N = 2e5 + 5;
const int LG = 22;
int tree_data[N * LG];
int* tree[2 * N];
int sz[2 * N];

void build(int n, int *arr) {
    for (int i = 0; i < n; i++) {
        sz[i + n] = 1;
    }
    for (int i = n - 1; i > 0; i--) {
        sz[i] = sz[i << 1] + sz[i << 1 | 1];
    }

    int* current_ptr = tree_data;
    for (int i = 1; i < 2 * n; i++) {
        tree[i] = current_ptr;
        current_ptr += sz[i];
    }

    for (int i = 0; i < n; i++) {
        tree[i + n][0] = arr[i];
    }

    for (int i = n - 1; i > 0; i--) {
        merge(tree[i << 1], tree[i << 1] + sz[i << 1],
              tree[i << 1 | 1], tree[i << 1 | 1] + sz[i << 1 | 1],
              tree[i]);
    }
}

int queryGreater(int l, int r, int n, int k) {
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            int* end_ptr = tree[l] + sz[l];
            res += (end_ptr - upper_bound(tree[l], end_ptr, k));
            l++;
        }
        if (r & 1) {
            --r;
            int* end_ptr = tree[r] + sz[r];
            res += (end_ptr - upper_bound(tree[r], end_ptr, k));
        }
    }
    return res;
}