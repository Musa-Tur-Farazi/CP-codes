
int n,m,a[N],pf[N],cnt[2000005];
int ans = 0;
int k;

//xor(l,r) = pf(r)^p(l-1) in que.l , minus
void add(int x){
    ans+=cnt[pf[x]^k];
    cnt[pf[x]]++;
}
void remove(int x){
    cnt[pf[x]]--;
    ans -= cnt[pf[x]^k];
}
const int SZ = 700;
struct Query {
    int l, r, idx;
    bool operator<(Query other) const{
        if(l/SZ!=other.l/SZ) return l/SZ < other.l/SZ;
        return r < other.r;
    }
};
vector<int>get(vector<Query> &queries) { //1-based
    vector<int>res((int)queries.size());
    sort(all(queries));
    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        while (cur_l > q.l) { cur_l--; add(cur_l); }
        while (cur_r < q.r) { cur_r++; add(cur_r); }
        while (cur_l < q.l) { remove(cur_l); cur_l++; }
        while (cur_r > q.r) { remove(cur_r); cur_r--; }
        res[q.idx] = ans;
    }
    return res;
}

void solve(int tc){
    cin >> n >> m >> k;
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) pf[i] = pf[i-1]^a[i-1];
    vector<Query> que(m);
    for(int i=0;i<m;i++){
        cin >> que[i].l >> que[i].r;
        --que[i].l; // que[i].r;
        que[i].idx = i;
    }
    auto ans = get(que);
    for(auto x : ans) cout << x << '\n';
}


//////////

//sum cnt[i]*cnt[i]*i
int n,q,a[N],cnt[1000005];
int ans = 0;

void add(int x){
    ans -= cnt[a[x]]*cnt[a[x]]*a[x];
    cnt[a[x]]++;
    ans += cnt[a[x]]*cnt[a[x]]*a[x];
}

void remove(int x){
    ans -= cnt[a[x]]*cnt[a[x]]*a[x];
    cnt[a[x]]--;
    ans += cnt[a[x]]*cnt[a[x]]*a[x];
}
const int SZ = 700;

struct Query {
    int l, r, idx;
    bool operator<(Query other) const{
        if(l/SZ!=other.l/SZ) return l/SZ < other.l/SZ;
        return r < other.r;
    }
};

vector<int>get(vector<Query> &queries) {
    vector<int>res((int)queries.size());
    sort(all(queries));

    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        res[q.idx] = ans;
    }
    return res;
}

