//0-based indexing with define int disabled
/*
* Wavelet_tree<T>(vT a) : O(n log n)
*
* T get(int i) : O(log n)
*	Returns the i-th element in ascending order.
*
* T get(int l, int r, int i) : O(log n))
*	Returns the i-th element in a[l..r) in ascending order.
*
* int count(int l, int r, T v) : O(log n)
*	 Returns how many v are in a[l..r)
*
* int count(int l, int r, T v0, T v1) : O(log n)
*	Returns the number of elements in a[l..r) that have the value [v0..v1).
*	Note: For the point group {(i, a[i])},
this can also be interpreted as finding the number of points that exist within the rectangle. ．．
*
* int position(T v, int c) : O((log n)^2)
*	Returns the c-th position of v in ascending order.
*
* ll sum(int l, int r) : O(1)
*	Returns the sum of a[l..r)
*
* ll sum(int l, int r, T v0, T v1) : O(log n)
*	Returns the sum of the elements in a[l..r) that have values in [v0..v1).
*
* ll abs_sum(int l, int r, T v) : O(log n)
*	for i -> [l..r) returns sum |a[i] - v|.
*/
template <class T>
class Wavelet_tree {
	int n;
	int k;
	vector<int> bs;
	array<vector<vector<int>>, 2> bs_acc;
	vector<int> num_zeros;
	vector<int> id;
	vector<vector<T>> acc;
	vector<T> val;

	int count_sub(int r, int v) {
		if (!id[v]) return 0;
		for(int j=k-1;j>=0;j--) {
			if (v >> j & 1) r = num_zeros[j] + bs_acc[1][j][r];
			else r = bs_acc[0][j][r];
		}
		return r - id[v];
	}
	int count_rsub(int l, int r, int v) {
		int cnt = 0;
		for(int j=k-1;j>=0;j--) {
			if(v >> j & 1){
				cnt += bs_acc[0][j][r]-bs_acc[0][j][l];
				r = num_zeros[j]+bs_acc[1][j][r];
				l = num_zeros[j]+bs_acc[1][j][l];
			}
			else r = bs_acc[0][j][r], l = bs_acc[0][j][l];
		}
		return cnt;
	}

	T sum_rsub(int l, int r, int v) {
		T res = 0;
		for(int j=k-1;j>=0;j--){
			if(v >> j & 1){
				res += acc[j][bs_acc[0][j][r]]-acc[j][bs_acc[0][j][l]];
				r = num_zeros[j]+bs_acc[1][j][r];
				l = num_zeros[j]+bs_acc[1][j][l];
			}
			else r = bs_acc[0][j][r], l = bs_acc[0][j][l];
		}
		return res;
	}

public:
	Wavelet_tree(const vector<T>& a) : n((int)(a.size())) {
		val = a;
		sort(all(val)); (val).erase(unique(all(val)), (val).end());
		val.emplace_back((T)inf + 1);
		vector<int> t(n);
		for(int i=0;i<n;i++) t[i] = (int)distance((val).begin(), lower_bound(all(val), a[i]));

        int sz = val.size();

		k = (sz!=0 ? (31 - __builtin_clz(n)) : -1) + 1;
		bs = vector<int>(n);
		bs_acc[0] = bs_acc[1] = vector<vector<int>>(k, vector<int>(n + 1));
		num_zeros = vector<int>(k);
		id = vector<int>((int)val.size(), -1);
		acc = vector<vector<T>>(k + 1, vector<T>(n + 1));

		for(int j=k-1;j>=0;j--) {
			for(int i=0;i<n;i++) {
				bs[i] += t[i] & T(1) << j;
				for(int b=0;b<2;b++) bs_acc[b][j][i + 1] = bs_acc[b][j][i];
				if (t[i] >> j & 1) bs_acc[1][j][i + 1]++;
				else bs_acc[0][j][i + 1]++, num_zeros[j]++;
				acc[j + 1][i + 1] = acc[j + 1][i] + val[t[i]];
			}

			vector<int> nt0, nt1;
			for(int i=0;i<n;i++) {
				if (t[i] >> j & 1) nt1.push_back(t[i]);
				else nt0.push_back(t[i]);
			}
			t.clear();
			for(auto x : nt0) t.push_back(x);
			for(auto x : nt1) t.push_back(x);
		}

		for(int i=0;i<n;i++) {
			if (id[t[i]] != -1) id[t[i]] = i;
			acc[0][i + 1] = acc[0][i] + val[t[i]];
		}
	}
	Wavelet_tree() : n(0), k(0){}
	int position(T v, int c) {
		int ord = (int)distance((val).begin(),lower_bound(all(val), v));
		if (val[ord] != v) return -1;
		int i = id[ord] + c;
		for(int j=0;j<k;j++){
		    auto up = upper_bound(all(bs_acc[ord >> j & 1][j]),i-num_zeros[j]);
            i = (int)distance((bs_acc[ord >> j & 1][j]).begin(),up)-1;
		}
		return i;
	}
	T get(int i) {
		assert(0 <= i && i < n);
		int ord = 0;

		for(int j=k-1;j>=0;j--){
			ord <<= 1;
			if (bs[i] >> j & 1) ord++, i = num_zeros[j] + bs_acc[1][j][i];
			else i = bs_acc[0][j][i];
		}
		return val[ord];
	}
	T get(int l, int r, int i) {
		l = max(l,0), r = min(r,n);
		assert(0 <= i && i < r - l);
		int ord = 0;
		for(int j=k-1;j>=0;j--){
			ord <<= 1;
			int cnt0 = bs_acc[0][j][r] - bs_acc[0][j][l];
			if (i >= cnt0) {
				ord++;
				l = num_zeros[j] + bs_acc[1][j][l];
				r = num_zeros[j] + bs_acc[1][j][r];
				i -= cnt0;
			}
			else{
				l = bs_acc[0][j][l];
				r = bs_acc[0][j][r];
			}
		}
		return val[ord];
	}

	int count(int l, int r, T v) {
		l = max(l,0), r = min(r,n);
		if (l >= r) return 0;
		int ord = (int)distance((val).begin(), lower_bound(all(val), v));
		if (val[ord] != v) return 0;
		return count_sub(r, ord) - count_sub(l, ord);
	}
	int count(int l, int r, T v0, T v1) {
		l = max(l,0), r = min(r,n);
		if (l >= r || v0 >= v1) return 0;
		int ord0 = (int)distance((val).begin(), lower_bound(all(val), v0));
		int ord1 = (int)distance((val).begin(), lower_bound(all(val), v1));
		return count_rsub(l, r, ord1) - count_rsub(l, r, ord0);
	}

	T sum(int l, int r) {
		l = max(l,0), r = min(r,n);
		if (l >= r) return 0;
		return acc[k][r] - acc[k][l];
	}
	T sum(int l, int r, T v0, T v1) {
		l = max(l,0), r = min(r,n);
		if (l >= r || v0 >= v1) return 0;
		int ord0 = (int)distance((val).begin(), lower_bound(all(val), v0));
		int ord1 = (int)distance((val).begin(), lower_bound(all(val), v1));
		return sum_rsub(l, r, ord1) - sum_rsub(l, r, ord0);
	}
	T abs_sum(int l, int r, T v) {
		l = max(l,0), r = min(r,n);
		if (l >= r) return 0;
		int ord = (int)distance((val).begin(), lower_bound(all(val), v));
		T res = sum_rsub(l, r, (1 << k) - 1);
		res -= (r - l) * v;
		res -= 2 * sum_rsub(l, r, ord);
		res += 2 * count_rsub(l, r, ord) * v;
		return res;
	}
};

void solution(){
    int n; cin >> n;
    vector<long long>a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    Wavelet_tree<long long> w(a);
    int q; cin >> q;
    long long b = 0;
    while(q--){
        long long L,R,X;
        cin >> L >> R >> X;
        int l = (int)(L^b);
        int r = (int)(R^b);
        long long x = X^b;
        l--;
        long long sum = w.sum(l,r,0,x+1);
        cout << sum << '\n';
        b = sum;
    }
}
