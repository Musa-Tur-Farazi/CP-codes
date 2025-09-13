//query count of min(x-a[i]) in [l,r] in O(n/B + B*Q) here Q = log(n) [per query]
const int B = 3000;

struct block{
    set<pair<int,int>>s;
    map<int,int>cnt;
}blk[N];

int a[N];
int bnum[N];

int upd(int i,int v){
    blk[bnum[i]].s.erase({a[i],i});
    blk[bnum[i]].cnt[a[i]]--;
    a[i]=v;
    blk[bnum[i]].s.insert({a[i],i});
    blk[bnum[i]].cnt[a[i]]++;
}

int qry(int l,int r,int x){
    int mxl = -inf , mnr = inf, cl = 0 , cr = 0;
    if(bnum[l]==bnum[r]){
        for(int i=l;i<=r;i++){
            if(a[i]<x){
                if(a[i]>mxl) mxl=a[i],cl=1;
                else if(a[i]==mxl) cl++;
            }
            else{
                if(a[i]<mnr) mnr=a[i],cr=1;
                else if(a[i]==mnr) cr++;
            }
        }
    }
    else{
        for(int i=l;bnum[i]==bnum[l];i++){
            if(a[i]<x){
                if(a[i]>mxl) mxl=a[i],cl=1;
                else if(a[i]==mxl) cl++;
            }
            else{
                if(a[i]<mnr) mnr=a[i],cr=1;
                else if(a[i]==mnr) cr++;
            }
        }
        for(int i=r;bnum[i]==bnum[r];i--){
            if(a[i]<x){
                if(a[i]>mxl) mxl=a[i],cl=1;
                else if(a[i]==mxl) cl++;
            }
            else{
                if(a[i]<mnr) mnr=a[i],cr=1;
                else if(a[i]==mnr) cr++;
            }
        }
        for(int i=bnum[l]+1;i<=bnum[r]-1;i++){
            auto it = blk[i].s.lower_bound({x,0});
            if(it!=blk[i].s.end()){
                if(it->first < mnr) mnr = it->first, cr = blk[i].cnt[it->first];
                else if(it->first==mnr) cr+=blk[i].cnt[it->first];
            }
            if(it==blk[i].s.begin()) continue;
            it--;
            if(it->first>mxl) mxl=it->first, cl=blk[i].cnt[it->first];
            else if(it->first==mxl) cl+=blk[i].cnt[it->first];
        }
    }
    int res = 0;
    if(mxl==-inf) res = cr;
    else if(mnr==inf) res = cl;
    else if(x-mxl==mnr-x) res=cr+cl;
    else if(x-mxl<mnr-x) res=cl;
    else res=cr;
    return res;
}

void solve(){
    int n,q; cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++){
        blk[i].s.clear();
        blk[i].cnt.clear();
    }
    for(int i=1;i<=n;i++){
        bnum[i]=i/B + 1;
        blk[bnum[i]].s.insert({a[i],i});
        blk[bnum[i]].cnt[a[i]]++;
    }
    while(q--){
        int t; cin >> t;
        if(t==1){
            int l,r,x; cin >> l >> r >> x;
            cout << qry(l,r,x) << '\n';
        }
        else{
            int i,v; cin >> i >> v;
            upd(i,v);
        }
    }
}
