
//Node x to y update and query for inv/non-inv function

int st[4*N+1];
int n, q, a[N];

void update(int i,int v){
    st[i+=n] = v;
    for(i/=2;i;i/=2) st[i] = max(st[i<<1],st[i<<1|1]);
}

int query(int l,int r){
    int resa = 0 , resb = 0;
    for(l+=n,r+=n+1;l<r;l/=2,r/=2){
        if(l&1) resa = max(resa,st[l++]);
        if(r&1) resb = max(resb,st[--r]);
    }
    return max(resa,resb);
}

int sz[N], par[N], dep[N];
int id[N], tp[N];
vector<int>adj[N];

void dfs(int u,int fa){
    sz[u] = 1;
    par[u] = fa;
    dep[u] = dep[fa] + 1;
    for(auto to : adj[u]){
        if(to==fa) continue;
        dfs(to,u);
        sz[u]+=sz[to];
    }
}

int t = 0;
void hld(int u,int fa,int top){
    id[u] = ++t;
    tp[u] = top;
    update(id[u],a[u]);
    int big = -1;
    for(auto to : adj[u]){
        if(to != fa && (big == -1 || sz[big] < sz[to])) big = to;
    }
    if(big == -1) return;
    hld(big,u,top);
    for(auto to : adj[u]){
        if(to!=fa && to != big) hld(to,u,to);
    }
}

int get(int x,int y){
    int res = -1;
    while(tp[x]!=tp[y]){
        if(id[tp[x]] > id[tp[y]]) swap(x,y);
        res = max(res,query(id[tp[y]],id[y]));
        y = par[tp[y]];
    }
    if(id[x] > id[y]) swap(x,y);
    res = max(res,query(id[x],id[y]));
    return res;
}

void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<n;i++){
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1,1);
    hld(1,1,1);
    while(q--){
        int t; cin >> t;
        if(t==1){
            int s,x; cin >> s >> x;
            a[s] = x;
            update(id[s],a[s]);
        }
        else{
            int a,b; cin >> a >> b;
            cout << get(a,b) << ' ';
        }
    }

}

bool multi_test = 0;

int32_t main(){
    I_love_you_Liny;
    int T = 1;
    if(multi_test) cin >> T;
    while(T--) solve();
    return 0;
}

