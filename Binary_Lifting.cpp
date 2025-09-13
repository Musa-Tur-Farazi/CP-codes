int par[N][LOG + 1];
int depth[N],sz[N];

void dfs(int u, int a = 0){
    par[u][0] = a;
    depth[u] = depth[a] + 1;
    sz[u] = 1;
    for(int i=1;i<=LOG;i++){
        par[u][i] = par[par[u][i-1]][i-1];
    }

    for(auto x : e[u]){
        if(x != a){
            dfs(x, u);
            sz[u]+=sz[x];
        }
    }
}

int kth(int u, int k){
    assert(k >= 0);
    for(int i=0;i<=LOG;i++){
        if(k & (1 << i)) u = par[i][u];
    }
    return u;
}

int lca(int u,int v){
    if(depth[u] < depth[v]) swap(u,v);
    for(int i = LOG; i>=0 ; i--){
        if(depth[par[u][i]]>=depth[v]) u = par[u][i];
    }
    if(u == v) return u;
    for(int i=LOG;i>=0;i--){
        if(par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    }
    return par[u][0];
}

inline int distance(int u,int v){  return depth[u] + depth[v] - 2*depth[lca(u,v)]; }

int get(int u,int v, int k){
    int l = lca(u,v);
    if(depth[l] + k <= depth[u]) return kth(u,v);
   // k -= depth[u] - depth[l];

    return kth(v, depth[v] - 2*depth[l] - k + depth[u]);
}
