
int a[N];
struct node{
     int mx;
} st[1<<19];

const int neutral = -inf;

void app(int i,int x,int l2,int r2){
    st[i].mx += x;
   // st[i].sum+=x*(r2-l2+1);
    st[i].lz += x;
}

void psh(int i,int l2,int m2,int r2){
    app(2*i,st[i].lz,l2,m2);
    app(2*i+1,st[i].lz,m2+1,r2);
    st[i].lz = 0;
}

void upd(int l1,int x,int i=1,int l2=0,int r2=n-1){
    if(l2==r2){
        st[i].mx = x;
        return;
    }
    int m2 = (l2+r2)/2;
    psh(i,l2,m2,r2);
    if(l1 <=m2) upd(l1,x,2*i,l2,m2);
    else upd(l1,x,2*i+1,m2+1,r2);
    st[i].mn = max(st[2*i].mx,st[2*i+1].mx);
}

void upd2(int l1,int r1,int x,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1){
        app(i,x,l2,r2);
        return;
    }
    int m2 = (l2 + r2)/2;
    psh(i,l2,m2,r2);
    if(l1<=m2) upd2(l1,r1,x,2*i,l2,m2);
    if(m2<r1) upd2(l1,r1,x,2*i+1,m2+1,r2);
    st[i].mn = max(st[2*i].mx,st[2*i+1].mx);
}


int qry(int l1,int r1,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1) return st[i].mx;
    int m2 = (l2+r2)/2;
    psh(i,l2,m2,r2);
    int left = (l1 <= m2) ? qry(l1,r1,2*i,l2,m2):neutral;
    int right = (m2<r1) ? qry(l1,r1,2*i+1,m2+1,r2):neutral;
    return max(left,right);
}

void solution(){
    cin >> n >> q;
    for(int i=0;i<n;i++) cin >> a[i], upd(i,a[i]);
    while(q--){
        int t; cin >> t;
        if(t==1){
            int a,b,u; cin >> a >> b >> u;
            --a,--b;
            upd2(a,b,u);
        }
        else{
            int k; cin >> k; --k;
            cout << qry(k,k) << '\n';
        }
    }

}

bool multi_test = 0;

int32_t main(){
    I_love_you_Liny;
    int T = 1;
    cout << setprecision(6) << fixed;
    if(multi_test) cin >> T;
    while(T--) solution();
    return 0;

}

