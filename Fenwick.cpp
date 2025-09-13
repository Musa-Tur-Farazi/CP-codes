template <class T>
struct fenwick { //1-indexed
    //Always calculates count of strictly smaller values
    //Ex : upd(a[i],1) => count of a[j] such that j<i & a[j]<a[i]
    // upd(a[i],a[i]) => sum of a[j] such that j<i & a[j]<a[i]
    // upd(a[i],f(a[i])) => sum of f(a[j]) such that j<i & a[j]<a[i]
    // starting from end gives all j s.t. j>i , starting from beginning gives all j s.t. j<i

    int n; vector<T> t;
    fenwick() {}
    fenwick(int _n) {
        n = _n; t.assign(n + 1, 0);
    }
    T query(int i) {
        T ans = 0;
        for (; i >= 1; i -= (i & -i)) ans += t[i];
        return ans;
    }
    void upd(int i, T val) {
        if (i <= 0) return;
        for (; i <= n; i += (i & -i)) t[i] += val;
    }
    void upd(int l, int r, T val) {
        upd(l, val); upd(r + 1, -val);
    }
    inline T query(int l, int r) { return query(r) - query(l - 1); }
};
