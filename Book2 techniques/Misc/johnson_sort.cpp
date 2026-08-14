struct job {
    int id, a, b, group;

    job(int a,int b,int id) : a(a), b(b), id(id) {
        if (a < b) group = 1;
        if (a == b) group = 2;
        if (a > b) group = 3;
    }

    bool operator<(const job &other) const {
        if (group != other.group)
            return group > other.group;
        if (group == 1)
            return a > other.a;
        if (group == 3)
            return b < other.b;
        return id > other.id;
    }
};
