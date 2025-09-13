struct segtree {
	vector<int>tr,lz;
	segtree(){}
	segtree(int n){
		tr.resize(4*n); lz.resize(4*n);
	}

	inline void propagate(int u, int st, int en) {
		if (lz[u] == 0) return;
		tr[u] = lz[u];       //Check here ...
		if (st != en) {
		  lz[2*u] = lz[2*u] + lz[u];
		  lz[2*u+1] = lz[2*u+1] + lz[u];
		}
		lz[u] = 0;
	  }
	inline int combine(int a,int b) {
		return a+b;
	}
	inline void pull(int u) {
		tr[u] = combine(tr[2*u],tr[2*u+1]);
	}
	void build(int u, int st, int en,int a[]) {
		lz[u] = 0;
		if(st == en) {
			tr[u] = a[st];
			return;
		}
		int mid = (st + en)/2;
		build(2*u, st, mid, a);
		build(2*u+1, mid+1, en, a);
		pull(u);
	}

	void update(int u, int st, int en, int l, int r, int v) {
		propagate(u, st, en);
		if (r < st || en < l) return;
		if (l <= st && en <= r) {
			lz[u] = v;             //set lazy
			propagate(u, st, en);
			return;
		}
		int mid = (st + en)/2;
		update(2*u, st, mid, l, r, v);
		update(2*u+1, mid + 1, en, l, r, v);
		pull(u);
	}

	void update(int l,int r) {
		update(1, 1, n, l, r);
	}

	int query(int u, int st, int en, int l, int r) {
		propagate(u, st, en);
		if (l > en || st > r) return 0;    //return null
		if (l <= st && en <= r) return tr[u];
		int mid = (st + en)/2;
		return combine(query(2*u, st, mid, l, r), query(2*u+1, mid + 1, en, l, r));
	}

	int query(int l, int r) {
		return query(1, 1, n, l, r);
	}

	int query_first_greater(int u, int st, int en, int l, int r, int x) {    // first a[i] > x
		if(st > r || en < l) return -1;
		if(tr[u] <= x) return -1;

		if (st== en) return st;
		int mid = (st+en)/2;
		int left = query_first_greater(2*u, st, mid, l, r, x);
		if(left != -1) return left;
		return query_first_greater(2*u+1, mid+1, en, l ,r, x);
	}
};
