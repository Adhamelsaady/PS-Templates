#include <bits/stdc++.h>
using namespace std;

/*
    KD-Tree: Maximum Nearest-Neighbor Manhattan Distance

    Given:
      - a static set of reference points
      - many query points

    For each query, find its Manhattan distance to the nearest
    reference point, then output the maximum of those distances.

    KD-tree nodes store bounding boxes.
    Bounding-box distance lets us prune subtrees that cannot improve
    the current nearest answer.

    Build: O(n log n)
    Query: very fast in practice; worst-case O(n)
*/


using ll = long long;

struct Point {
    ll x, y;
};

static ll manhattan(const Point& a, const Point& b) {
    return llabs(a.x - b.x) + llabs(a.y - b.y);
}

class KDTree {
    struct Node {
        Point p;
        int left = -1, right = -1;
        ll minX, maxX, minY, maxY;
    };

    vector<Node> tree;
    int root = -1;

    static ll boxDistance(const Node& node, const Point& q) {
        ll dx = 0, dy = 0;

        if (q.x < node.minX) dx = node.minX - q.x;
        else if (q.x > node.maxX) dx = q.x - node.maxX;

        if (q.y < node.minY) dy = node.minY - q.y;
        else if (q.y > node.maxY) dy = q.y - node.maxY;

        return dx + dy;
    }

    int build(vector<Point>& pts, int l, int r) {
        if (l >= r) return -1;

        ll minX = pts[l].x, maxX = pts[l].x;
        ll minY = pts[l].y, maxY = pts[l].y;

        for (int i = l + 1; i < r; ++i) {
            minX = min(minX, pts[i].x);
            maxX = max(maxX, pts[i].x);
            minY = min(minY, pts[i].y);
            maxY = max(maxY, pts[i].y);
        }

        bool splitX = (maxX - minX >= maxY - minY);
        int mid = (l + r) / 2;

        if (splitX) {
            nth_element(
                pts.begin() + l, pts.begin() + mid, pts.begin() + r,
                [](const Point& a, const Point& b) {
                    return a.x != b.x ? a.x < b.x : a.y < b.y;
                }
            );
        } else {
            nth_element(
                pts.begin() + l, pts.begin() + mid, pts.begin() + r,
                [](const Point& a, const Point& b) {
                    return a.y != b.y ? a.y < b.y : a.x < b.x;
                }
            );
        }

        int id = (int)tree.size();
        tree.push_back({pts[mid], -1, -1, minX, maxX, minY, maxY});

        int leftChild = build(pts, l, mid);
        int rightChild = build(pts, mid + 1, r);

        tree[id].left = leftChild;
        tree[id].right = rightChild;
        return id;
    }

    void nearestDFS(int id, const Point& q, ll& best) const {
        if (id == -1) return;

        const Node& node = tree[id];
        if (boxDistance(node, q) >= best) return;

        best = min(best, manhattan(node.p, q));
        if (best == 0) return;

        int a = node.left;
        int b = node.right;

        ll da = (a == -1 ? LLONG_MAX : boxDistance(tree[a], q));
        ll db = (b == -1 ? LLONG_MAX : boxDistance(tree[b], q));

        if (da > db) {
            swap(a, b);
            swap(da, db);
        }

        if (a != -1 && da < best) nearestDFS(a, q, best);
        if (b != -1 && db < best) nearestDFS(b, q, best);
    }

public:
    explicit KDTree(vector<Point> pts) {
        tree.reserve(pts.size());
        root = build(pts, 0, (int)pts.size());
    }

    ll nearestDistance(const Point& q) const {
        ll best = LLONG_MAX;
        nearestDFS(root, q, best);
        return best;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<Point> reference(n);
    for (auto& p : reference)
        cin >> p.x >> p.y;

    KDTree kd(reference);

    ll answer = 0;
    while (q--) {
        Point p;
        cin >> p.x >> p.y;
        answer = max(answer, kd.nearestDistance(p));
    }

    cout << answer << '\n';
}
