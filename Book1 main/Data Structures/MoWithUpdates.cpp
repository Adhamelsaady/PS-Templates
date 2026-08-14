const int N = 2e5 + 5, SQ = 3500;

struct query {
    int l, r, idx, uIdx;

    bool operator<(const query &other) const {
        if (l / SQ != other.l / SQ)
            return l / SQ < other.l / SQ;
        if (r / SQ != other.r / SQ)
            return r / SQ < other.r / SQ;
        return uIdx < other.uIdx;
    }
};

struct update {
    int idx, val, old;
};

int a[N], ans[N], frq[N], cnt[N];

void add(int idx) {
    cnt[frq[a[idx]]]--;
    frq[a[idx]]++;
    cnt[frq[a[idx]]]++;
}

void del(int idx) {
    cnt[frq[a[idx]]]--;
    frq[a[idx]]--;
    cnt[frq[a[idx]]]++;
}

void redo(update &u, int l, int r) {
    if (u.idx >= l && u.idx <= r)del(u.idx);
    a[u.idx] = u.val;
    if (u.idx >= l && u.idx <= r)add(u.idx);
}

void undo(update &u, int l, int r) {
    if (u.idx >= l && u.idx <= r)del(u.idx);
    a[u.idx] = u.old;
    if (u.idx >= l && u.idx <= r)add(u.idx);
}


void GO(vector<query> &v, vector<update> &u) {
    int l = 0, r = -1;
    int cur = 0;
    for (auto &q: v) {
        while (cur < q.uIdx)redo(u[cur++], l, r);
        while (cur > q.uIdx)undo(u[--cur], l, r);
        while (r < q.r)add(++r);
        while (l > q.l)add(--l);
        while (r > q.r)del(r--);
        while (l < q.l)del(l++);
        while (cnt[ans[q.idx]])ans[q.idx]++;
    }
}