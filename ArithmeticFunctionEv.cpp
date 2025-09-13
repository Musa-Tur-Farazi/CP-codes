const int MAXN = 10000005;
vector <int> prime;
bool is_composite[MAXN];
int func[MAXN], cnt[MAXN];

void sieve (int n) {
	fill (is_composite, is_composite + n, false);
	func[1] = 1;
	for (int i = 2; i < n; ++i) {
		if (!is_composite[i]) {
			prime.push_back (i);
			func[i] = 1; cnt[i] = 1;
		}
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			is_composite[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				func[i * prime[j]] = func[i] / cnt[i] * (cnt[i] + 1);
				cnt[i * prime[j]] = cnt[i] + 1;
				break;
			} else {
				func[i * prime[j]] = func[i] * func[prime[j]];
				cnt[i * prime[j]] = 1;
			}
		}
	}
}


int get(int x){
    //phi(n) = sum over div d of mu(d)*x/d
    int res = 0;
    auto v = factorize(x);
    int sz = v.size();
    for(int msk=0;msk<(1<<sz);msk++){
        int prd = 1;
        int cnt = __builtin_popcount(msk);
        for(int i=0;i<sz;i++){
            if(msk>>i&1) prd*=v[i];
        }
        if(cnt&1) res-=(x/prd);
        else res+=(x/prd);
    }
    return res;
}

void calc(){
	//f(n) = sum(k*phi(k) such that k|n)
    f[1] = 1 ;
    for(int i=2;i<=SIEVE;i++){
        int p = lp[i];
        int cur = p;
        while(i%(cur*p)==0) cur*=p;
        if(cur==i) f[i] = i*phi[i] + f[i/p];
        else f[i] = f[i/cur]*f[cur];
    }
}

