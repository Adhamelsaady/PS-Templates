int SQ , res = 0; // Set it to ceil(sqrt(n));

const int N = 2e5 + 10;
int arr[N] , ans[N] , n , q;

struct Query {
    int l, r, idx;
    bool operator<(Query &other) {
        if (l / SQ != other.l / SQ)
            return l / SQ < other.l / SQ;
        return (l / SQ & 1 ? r < other.r : r > other.r);
    }
};

vector <Query> queries; // Resizeeeeeeee

void add(int idx){
    // Logic
}

void del(int idx){
    // Logic
}

int query() {
    return res;
}

void calc() {
    sort(queries.begin(), queries.end());
    int l = 0 , r = -1;
    for (auto &[lq, rq, idx]: queries) {
        while (l > lq) add(--l);
        while (r < rq) add(++r);
        while (l < lq) del(l++);
        while (r > rq) del(r--);
        ans[idx] = query();
    }
}
