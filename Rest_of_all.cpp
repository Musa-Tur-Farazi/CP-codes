/*DP from CSES + AtCoder*/

1. LIS in O(nlog n)
    int n;
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];

    vector<int>dp;
    for(int i=1;i<=n;i++){
        int x = lower_bound(dp.begin(),dp.end(),a[i])-dp.begin();
        if(x==dp.size()){
            dp.push_back(a[i]);
        }
        else{
            dp[x] = a[i];
        }

    }
    cout << dp.size() << '\n';
/**********************************/

2. There are n projects you can attend. For each project, you know its starting and ending days and the amount of money you would get as reward.
You can only attend one project during a day.
What is the maximum amount of money you can earn?

int dp[N];

void solution(){
       int n; cin >> n;
       vector<array<int,3>>a(n);
       for(int i=0;i<n;i++) cin >> a[i][0] >> a[i][1] >> a[i][2];
       sort(all(a),[&](array<int,3>&p,array<int,3>&q){
              if(p[1] < q[1]) return true;
              if(p[1] == q[1]) return p[0] < q[0];
              else return false;
       });

       vector<int>tmp(n);
       for(int i=0;i<n;i++) tmp[i] = a[i][1];
       dp[0] = a[0][2];
       cerr << tmp << '\n';
       for(int i=1;i<n;i++){
              int k = lower_bound(all(tmp),a[i][0]) - tmp.begin();
              if(k > 0) dp[i] = max(dp[max(0LL,k-1)] + a[i][2],dp[i-1]);

              else dp[i] = max(dp[i-1],a[i][2]);
       }
       cout << dp[n-1] << '\n';
}

/******************************************/
3. There are n people who want to get to the top of a building which has only one elevator.
You know the weight of each person and the maximum allowed weight in the elevator.
What is the minimum number of elevator rides?

pair<int,int>dp[1<<20];

void solution(){
    int n,x; cin >> n >> x;
    vector<int>w(n); cin >> w;
    dp[0] = {0,x+1};
    for(int i=1;i<(1<<n);i++){
        dp[i] = {25,0};
        for(int j=0;j<n;j++){
            if(i & (1LL << j)){
                auto now = dp[i^(1<<j)];
                if(now.second + w[j]<=x) now.second+=w[j];
                else{
                    now.first++;
                    now.second = min(now.second,w[j]);
                }
                dp[i] = min(dp[i],now);
            }
        }
    }
    cout << dp[(1<<n)-1].first<< '\n';
}
/*************************************/

4.You have n coins with certain values. Your task is to find all money sums you can create using these coins.
    int n; cin >> n;
    vector<int> v(n);
    for(int i=0;i<n;i++) cin >> v[i];

    vector<int> dp(100005);

    int s = accumulate(v.begin(),v.end(),0LL);
    dp[0]=1;
    for(int i=0;i<n;i++){
        for(int j=s+1;j>=0;j--){
            if(v[i]==j) dp[j] = 1;
            if(v[i]<=j) dp[j] = dp[j]|dp[j-v[i]];
        }
    }
    vector<int> a;
    for(int i=1;i<s+1;i++) if(dp[i]) a.push_back(i);
    cout << a.size() << "\n";
    for(auto x : a) cout << x << " ";

/*************************/

5. Your task is to count the number of integers between a and b
 where no two adjacent digits are the same.

bool tight[maxN];
ll dp[10][maxN];

ll solve(ll x){
    if(x <= 10) return x;

    vector<int> D;
    memset(dp, 0, sizeof(dp));
    memset(tight, 0, sizeof(tight));
    for(int i = 0; x; i++){
        D.push_back(x%10);
        x /= 10;
    }
    reverse(D.begin(), D.end());
    int N = (int) D.size();

    tight[0] = true;
    for(int i = 1; i < N; i++)
        tight[i] = tight[i-1] && (D[i] != D[i-1]);
    for(int d = 1; d < D[0]; d++)
        dp[d][0] = 1;

    for(int i = 1; i < N; i++){
        // Prefix [0..i-1] is same as X
        if(tight[i-1])
            for(int d = 0; d < D[i]; d++)
                if(d != D[i-1])
                    dp[d][i]++;

        // Prefix [0..i-1] is all leading zeros
        for(int d = 1; d <= 9; d++)
            dp[d][i]++;

        //  All other cases
        for(int d1 = 0; d1 <= 9; d1++)
            for(int d2 = 0; d2 <= 9; d2++)
                if(d1 != d2)
                    dp[d2][i] += dp[d1][i-1];
    }

    ll cnt = tight[N-1];
    for(int d = 0; d <= 9; d++)
        cnt += dp[d][N-1];
    return cnt;
}

int main(){
    ll a, b;
    scanf("%lld %lld", &a, &b);
    printf("%lld\n", solve(b) - solve(a-1));
}
/*****************************/
6. 0-1 knapsack when W is large and N small

    int n,W;
    cin >> n >> W;
    vector<int>v(n+1),w(n+1);
    for(int i=1;i<=n;i++){
        cin >> w[i] >> v[i];
    }
    dp[0] = 0;
    for(int i=1;i<=N;i++) dp[i] = inf;
    for(int i=1;i<=n;i++){
        for(int j=N;j>=v[i];j--){
            dp[j] = min(dp[j],dp[j-v[i]]+w[i]);
        }
    }
    int res = 0;
    for(int i=0;i<=N;i++){
        if(dp[i]<=W) res = i;
    }

    cout << res << '\n'
/***********************************/

7. [L,R] dp: There are
N slimes lining up in a row. Initially, the
i-th slime from the left has a size of a_i

Taro is trying to combine all the slimes into a larger slime. He will perform the following operation repeatedly until there is only one slime:

Choose two adjacent slimes, and combine them into a new slime. The new slime has a size of
x+y, where
x and y are the sizes of the slimes before combining them. Here, a cost of
x+y is incurred. The positional relationship of the slimes does not change while combining slimes.
Find the minimum possible total cost incurred.

    int n; cin >> n;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];

    vector<int>s(n+1);
    for(int i=1;i<=n;i++){
        s[i] = s[i-1] + a[i];
    }

    for(int j=1;j<=n;j++){
        for(int i=j-1;i>=1;i--){
            int mn = inf;
            for(int k=i;k<j;k++){
                mn = min(mn,dp[i][k]+dp[k+1][j]+s[j]-s[i-1]);
            }
            dp[i][j] = mn;
        }
    }
    cout << dp[1][n] << '\n';

/***********************/
/*Range queries*/

1. You are given a list consisting of n
 integers. Your task is to remove elements from the list at given positions, and report the removed elements.

 int n; cin >> n;
    vector<int>a(n); cin >> a;
    vector<int>b(n); cin >> b;
    --b;
    orset<pair<int,int>>o;
    for(int i=0;i<n;i++){
        o.insert({i,a[i]});
    }
    vector<int>res(n);
    for(int i=0;i<n;i++){
        auto now = *o.find_by_order(b[i]);
        cout << now.second << ' ';
        o.erase(now);
    }
/*******************/
2. A company has n employees with certain salaries. Your task is to keep track of the salaries and process queries.

Input

The first input line contains two integers n
 and q : the number of employees and queries. The employees are numbered 1,2,…,n.

The next line has n integers p1,p2,…,pn : each employee's salary.

After this, there are q lines describing the queries. Each line has one of the following forms:
! k x : change the salary of employee k to x

? a b : count the number of employees whose salary is between a…b

 int n,q;
    cin >> n >> q;
    vector<int>a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    orset<pair<int,int>>o;
    for(int i=1;i<=n;i++) o.insert({a[i],i});

    while(q--){
        char c;
        cin >> c;
        if(c=='!'){
            int k,x;
            cin >> k >> x;
            o.erase({a[k],k});
            a[k] = x;
            o.insert({a[k],k});
        }
        else{
            int p,q;
            cin >> p >> q;
            cout << o.order_of_key({q,mod}) - o.order_of_key({p-1,mod}) << '\n';
        }
    }
/*******************************/
3. You are given an array of n integers and q
 queries of the form: how many distinct values are there in a range [a,b] ?


template <typename T>
class fenwick {
      public:
      vector<T> fenw;
      int n;
      fenwick(int _n) : n(_n) {
        fenw.resize(n);
      }
      void modify(int x, T v) {
        while (x <= n) {
          fenw[x] += v;
          x += (x & -x);
        }
      }
      T get(int x) {
        T v{};
        while (x > 0) {
          v += fenw[x];
          x -= (x & -x);
        }
        return v;
      }

      T get(int l,int r){
        return get(r)-get(l-1);
      }

      T find(int x){

        T num = 0;
        T sum = 0;
        for(int i = 21; i>=0 ; --i){
            if((num + (1<<i) <= n) && (sum + fenw[num + (1<<i)] <= x)){
                num += (1<<i);
                sum += fenw[num];
            }
        }
        return num + 1;
      }

};
//1 based index

void solution(){
    int n,q;
    cin >> n >> q;
    vector<int>a(n);
    vector<vector<pair<int,int>>>que(n);
    cin >> a;
    for(int i=0;i<q;i++){
        int x,y;
        cin >> x >> y;
        --x,--y;
        que[x].push_back({y,i});

    }
    fenwick<int>ft(n+5);
    map<int,int>last;
    vector<int>res(q,-1);
    for(int i=n-1;i>=0;i--){
        int val = a[i];
        if(last.count(val)>0) ft.modify(last[val]+1,-1);
        last[val] = i;
        ft.modify(i+1,1);

        for(auto x : que[i]){
            res[x.second] = ft.get(x.first+1);
        }
    }
    for(auto x : res){
        cout << x << '\n';
    }
}
/*********************************/
4. You are given an n×n
 grid representing the map of a forest. Each square is either empty or has a tree. Your task is to process q
 queries of the following types:
 -Change the state (empty/tree) of a square.
 -How many trees are inside a rectangle in the forest?

int n,q;
int a[N];
int ft[1005][1005];

void upd(int i2,int j2,int x){
    for(int i=i2+1;i<=n;i+=i & -i)
    for(int j=j2+1;j<=n;j+=j & -j){
        ft[i][j]+=x;
    }
}

int qry(int i2,int j2){
    int res = 0;
    for(int i=i2;i;i-=i&-i){
        for(int j=j2;j;j-=j&-j) res+=ft[i][j];
    }
    return res;
}


void solution(){
    cin >> n >> q;
    vector<string>s(n);
    for(int i=0;i<n;i++){
        cin >> s[i];
        for(int j=0;j<n;j++){
            if(s[i][j]=='.') upd(i,j,0);
            else upd(i,j,1);
        }
    }
    while(q--){
        int t; cin >> t;
        if(t==1){
            int y,x; cin >> y >> x;
            --y, --x;
            if(s[y][x]=='.') upd(y,x,+1), s[y][x]='#';
            else upd(y,x,-1), s[y][x]='.';
        }
        else{
            int y1,x1,y2,x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << qry(y2,x2)-qry(y1-1,x2)-qry(y2,x1-1)+qry(y1-1,x1-1) << '\n';
        }

    }
/*****************************************/
5. Your task is to maintain an array of n
 values and efficiently process the following types of queries:
-Increase each value in range [a,b] by x.
-Set each value in range [a,b]to x.
-Calculate the sum of values in range [a,b].

int n,q;
int a[N];

struct node{
     int lz,sum;
     bool lz2;
} st[1<<19];

const int neutral = 0;

void app(int i,int x,bool w,int l2,int r2){
    if(w){
        st[i].sum = 0;
        st[i].lz = 0;
        st[i].lz2 = true;
    }
    st[i].sum+=x*(r2-l2+1);
    st[i].lz += x;

}

void psh(int i,int l2,int m2,int r2){
    app(2*i,st[i].lz,st[i].lz2,l2,m2);
    app(2*i+1,st[i].lz,st[i].lz2,m2+1,r2);
    st[i].lz = 0;
    st[i].lz2 = 0;
}

void upd(int l1,int x,int i=1,int l2=0,int r2=n-1){
    if(l2==r2){
        st[i].sum = x;
        return;
    }
    int m2 = (l2+r2)/2;
    psh(i,l2,m2,r2);
    if(l1 <=m2) upd(l1,x,2*i,l2,m2);
    else upd(l1,x,2*i+1,m2+1,r2);
    st[i].sum = st[2*i].sum+st[2*i+1].sum;
}

void upd2(int l1,int r1,int x,bool w,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1){
        app(i,x,w,l2,r2);
        return;
    }
    int m2 = (l2 + r2)/2;
    psh(i,l2,m2,r2);
    if(l1<=m2) upd2(l1,r1,x,w,2*i,l2,m2);
    if(m2<r1) upd2(l1,r1,x,w,2*i+1,m2+1,r2);
    st[i].sum = st[2*i].sum+st[2*i+1].sum;
}


int qry(int l1,int r1,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1) return st[i].sum;
    int m2 = (l2+r2)/2;
    psh(i,l2,m2,r2);
    int left = (l1 <= m2) ? qry(l1,r1,2*i,l2,m2):neutral;
    int right = (m2<r1) ? qry(l1,r1,2*i+1,m2+1,r2):neutral;
    return left+right;
}


void solution(){
    cin >> n >> q;
    for(int i=0;i<n;i++) cin >> a[i], upd(i,a[i]);
    while(q--){
        int t; cin >> t;
        if(t==1){
            int a,b,x;
            cin >> a >> b >> x;
            --a, --b;
            upd2(a,b,x,0);
        }else if(t==2){
            int a,b,x;
            cin >> a >> b >> x;
            --a,--b;
            upd2(a,b,x,1);
        }else{
            int a,b; cin >> a >> b;
            --a,--b;
            cout << qry(a,b) << '\n';
        }
    }
}
/*************************************/

6. Your task is to maintain an array of n
 values and efficiently process the following types of queries:
-Increase the first value in range [a,b]
 by 1, the second value by 2, the third value by 3, and so on.
-Calculate the sum of values in range [a,b].

int n,q;
int a[N];

struct node{
     int lz1,lz2,sum;
} st[1<<19];

const int neutral = 0;

void app(int i,int x,int x2,int l2,int r2){
   st[i].lz1+=x;
   st[i].lz2+=x2;
   st[i].sum+=(r2-l2+1)*x + x2*((r2+1)*r2/2 - (l2-1)*l2/2);

}

void psh(int i,int l2,int m2,int r2){
    app(2*i,st[i].lz1,st[i].lz2,l2,m2);
    app(2*i+1,st[i].lz1,st[i].lz2,m2+1,r2);
    st[i].lz1 = 0;
    st[i].lz2 = 0;
}

void upd(int l1,int x,int i=1,int l2=0,int r2=n-1){
    if(l2==r2){
        st[i].sum = x;
        return;
    }
    int m2 = (l2+r2)/2;
    psh(i,l2,m2,r2);
    if(l1 <=m2) upd(l1,x,2*i,l2,m2);
    else upd(l1,x,2*i+1,m2+1,r2);
    st[i].sum = st[2*i].sum+st[2*i+1].sum;
}

void upd2(int l1,int r1,int x,int w,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1){
        app(i,x,w,l2,r2);
        return;
    }
    int m2 = (l2 + r2)/2;
    psh(i,l2,m2,r2);
    if(l1<=m2) upd2(l1,r1,x,w,2*i,l2,m2);
    if(m2<r1) upd2(l1,r1,x,w,2*i+1,m2+1,r2);
    st[i].sum = st[2*i].sum+st[2*i+1].sum;
}


int qry(int l1,int r1,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1) return st[i].sum;
    int m2 = (l2+r2)/2;
    psh(i,l2,m2,r2);
    int left = (l1 <= m2) ? qry(l1,r1,2*i,l2,m2):neutral;
    int right = (m2<r1) ? qry(l1,r1,2*i+1,m2+1,r2):neutral;
    return left+right;
}


void solution(){
    cin >> n >> q;
    for(int i=0;i<n;i++) cin >> a[i], upd(i,a[i]);
    while(q--){
        int t; cin >> t;
        if(t==1){
            int a,b;
            cin >> a >> b;
            --a,--b;
            upd2(a,b,1-a,1);
        }
        else{
            int a,b;
            cin >>a >> b;
            --a,--b;
            cout << qry(a,b) << '\n';
        }
    }
}
/***************************************/

7. There is an array consisting of n integers. Some values of the array will be updated, and after each update,
your task is to report the maximum subarray sum in the array.

int n,q;
int a[N];

struct node{
     int sum,mxl,mxr,mx;
} st[1<<19];

const int neutral = 0;
/*
void app(int i,int x,int x2,int l2,int r2){
   st[i].lz1+=x;
   st[i].lz2+=x2;
   st[i].sum+=(r2-l2+1)*x + x2*((r2+1)*r2/2 - (l2-1)*l2/2);

}

void psh(int i,int l2,int m2,int r2){
    app(2*i,st[i].lz1,st[i].lz2,l2,m2);
    app(2*i+1,st[i].lz1,st[i].lz2,m2+1,r2);
    st[i].lz1 = 0;
    st[i].lz2 = 0;
}
*/
void upd(int l1,int x,int i=1,int l2=0,int r2=n-1){
    if(l2==r2){
        st[i].sum = x;
        st[i].mx = x;
        st[i].mxl = st[i].mxr = x;
        return;
    }
    int m2 = (l2+r2)/2;
    if(l1 <=m2) upd(l1,x,2*i,l2,m2);
    else upd(l1,x,2*i+1,m2+1,r2);
    st[i].sum = st[2*i].sum+st[2*i+1].sum;
    st[i].mx = max({st[2*i].mx,st[2*i+1].mx,st[2*i].mxr + st[2*i+1].mxl});
    st[i].mxl = max(st[2*i].mxl,st[2*i].sum + st[2*i+1].mxl);
    st[i].mxr = max(st[2*i+1].mxr,st[2*i+1].sum + st[2*i].mxr);
}
/*
void upd2(int l1,int r1,int x,int w,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1){
        app(i,x,w,l2,r2);
        return;
    }
    int m2 = (l2 + r2)/2;
    psh(i,l2,m2,r2);
    if(l1<=m2) upd2(l1,r1,x,w,2*i,l2,m2);
    if(m2<r1) upd2(l1,r1,x,w,2*i+1,m2+1,r2);
    st[i].sum = st[2*i].sum+st[2*i+1].sum;
}
*/

int qry(int l1,int r1,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1) return st[i].sum;
    int m2 = (l2+r2)/2;
//    psh(i,l2,m2,r2);
    int left = (l1 <= m2) ? qry(l1,r1,2*i,l2,m2):neutral;
    int right = (m2<r1) ? qry(l1,r1,2*i+1,m2+1,r2):neutral;
    return left+right;
}
void solution(){
    cin >> n >> q;
    for(int i=0;i<n;i++) cin >> a[i], upd(i,a[i]);
    while(q--){
        int k,x;
        cin >> k >> x;
        upd(--k,x);
        cout << max(st[1].mx,0LL) << '\n';
    }
}
/***************************************/


/*Mathematics + random + Geometry*/
1. Given a list of n positive integers,
your task is to count the number of pairs of integers that are coprime.
    int n; cin >> n;
    for(int i=0;i<n;i++){
        int x; cin >> x; freq[x]++;
    }
    for(int i=1;i<=N;i++){
        for(int j=i+i;j<=N;j+=i){ freq[i]+=freq[j];
        }
        freq[i]=freq[i]*(freq[i]-1)/2; // k_tuple: nCk
    }
    for(int i=N;i>=1;i--){
        for(int j=i+i;j<=N;j+=i){
            freq[i]-=freq[j];
        }
    }
    cout << freq[1] << '\n';

2. Given a list of n
 integers, your task is to calculate for each element x :
the number of elements y
 such that x or y=x

the number of elements y
 such that x&y=x

the number of elements y
 such that x&y≠0

const int N = 1 << 20;
const int LOG = 20;

void addToSuper(int dp[]){
    for(int bit=0;bit<LOG;bit++){
        for(int i=0;i<N;i++){
            if(i & (1 << bit)) dp[i]+=dp[i^(1<<bit)];
        }
    }
}
void back1(int dp[]){
    for(int bit=0;bit<LOG;bit++){
        for(int i=N-1;i>=0;i--){
            if(i&(1<<bit)) dp[i]-=dp[i^(1<<bit)];
        }
    }
}

void addToSub(int dp[]){
    for(int bit=0;bit<LOG;bit++){
        for(int i=N-1;i>=0;i--){
            if(i&(1<<bit)) dp[i^(1<<bit)]+=dp[i];
        }
    }
}

void back2(int dp[]){
    for(int bit=0;bit<LOG;bit++){
        for(int i=0;i<N;i++){
            if(i&(1<<bit)) dp[i^(1<<bit)]-=dp[i];
        }
    }
}
int freq1[N];
int freq2[N];

void solution(){
    int n;
    cin >> n;
    int a[n];
    for(int i=0;i<n;i++){
        cin >> a[i];
        freq1[a[i]]++;
        freq2[a[i]]++;
    }
    addToSuper(freq1);
    addToSub(freq2);
    for(int i=0;i<n;i++){
        int ans1 = freq1[a[i]];
        int ans2 = freq2[a[i]];
        int ans3 = n - freq1[(N-1)^a[i]];
        cout << ans1 << ' ' << ans2 << ' ' << ans3 << '\n';
    }
}
/************************************/

Maximum xor subarray :
int tri[N*30][2],cur = 0;
void insert(int x){
    int node = 0;
    for(int i=30;i>=0;i--){
        int y = x>>i&1;
        if(!tri[node][y]) tri[node][y] = ++cur;
        node = tri[node][y];
    }
}

int search(int x){
    int res = 0, node = 0;
    for(int i=30;i>=0;i--){
        int y = x>>i&1;
        if(tri[node][y^1]){
            node = tri[node][y^1]; res+=(1<<i);
        }
        else node = tri[node][y];
    } return res;
}
void solution(){
    int n; cin >> n; int xr = 0, mx = 0;
    insert(xr);
    for(int i=0;i<n;i++){
        int x; cin >> x; xr^=x; insert(xr);
    mx = max(search(xr),mx);
    } cout << mx << '\n';
}
/***********************************/

4.Given a set of points in the two-dimensional plane, your task is to find the minimum Euclidean distance between two distinct points.

#define int long long
#define endl '\n'
#define P pair<int, int>
#define X first
#define Y second

int norm(P a, P b) {
    return (b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y);
}

signed main(){
    int n; cin>>n;
    vector<P> v(n);
    int d = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[i] = {x, y};
    }
    sort(v.begin(), v.end());
    set<P> s = {{v[0].Y, v[0].X}};
    int j = 0;
    for (int i = 1; i < n; i++) {
        auto it = s.begin();
        int dd = ceil(sqrt(d));
        while (j < i && v[j].X < v[i].X - dd) {
            s.erase({v[j].Y, v[j].X});
            j++;
        }

        auto l = s.lower_bound({v[i].Y - dd, 0});
        auto r = s.upper_bound({v[i].Y + dd, 0});
        for (auto it = l; it != r; it++) {
            d = min(d, norm({it->Y, it->X}, v[i]));
        }
        s.insert({v[i].Y, v[i].X});
    }
    cout << d;
}

5. There are two line segments: the first goes through the points (x1,y1)
 and (x2,y2), and the second goes through the points (x3,y3) and (x4,y4).
Your task is to determine if the line segments intersect, i.e., they have at least one common point.

#define int long long
#define endl '\n'
#define P complex<int>
#define X real()
#define Y imag()

int cross(P a, P b, P c) {
    P u = b - a;
    P v = c - a;
    return (conj(u)*v).Y;
}

bool comp(const P &a, const P &b) {
    return (a.X == b.X) ? (a.Y < b.Y) : (a.X < b.X);
}

bool mid(P a, P b, P c) {
    vector<P> v = {a, b, c};
    sort(v.begin(), v.end(), comp);
    return (v[1] == c);
}

int sgn(int x) {
    return (x > 0) - (x < 0);
}

bool check(P a, P b, P c, P d) {
    int cp1 = cross(a, b, c);
    int cp2 = cross(a, b, d);
    int cp3 = cross(c, d, a);
    int cp4 = cross(c, d, b);
    if (cp1 == 0 && mid(a, b, c)) return 1;
    if (cp2 == 0 && mid(a, b, d)) return 1;
    if (cp3 == 0 && mid(c, d, a)) return 1;
    if (cp4 == 0 && mid(c, d, b)) return 1;
    if (sgn(cp1) != sgn(cp2) && sgn(cp3) != sgn(cp4)) return 1;
    return 0;
}


signed main(){
    int t; cin>>t;
    while (t--) {
        int x, y;
        P a, b, c, d;
        cin >> x >> y; a = {x, y};
        cin >> x >> y; b = {x, y};
        cin >> x >> y; c = {x, y};
        cin >> x >> y; d = {x, y};
        cout << (check(a, b, c, d) ? "YES" : "NO") << endl;
    }
}
/************************************/
6. Your task is to calculate the area of a given polygon.

The polygon consists of n vertices (x1,y1),(x2,y2),…,(xn,yn). The vertices (xi,yi) and (xi+1,yi+1)
are adjacent for i=1,2,…,n−1, and the vertices (x1,y1) and (xn,yn) are also adjacent.

#define X first
#define Y second

signed main(){
    int n; cin>>n;
    pair<int,int> a[n];
    for (int i = 0; i < n; i++)
        cin>>a[i].X>>a[i].Y;
    int ans = 0;
    //shoelace formula
    for (int i = 0; i < n; i ++) {
        ans += (a[i].X*a[(i+1)%n].Y - a[(i+1)%n].X*a[i].Y);
    }
    cout<<abs(ans);
}

/*********************************/

7.You are given a polygon of n vertices and a list of m points.
 Your task is to determine for each point if it is inside, outside or on the boundary of the polygon.

The polygon consists of n
 vertices (x1,y1),(x2,y2),…,(xn,yn)
. The vertices (xi,yi)
 and (xi+1,yi+1)
 are adjacent for i=1,2,…,n−1
, and the vertices (x1,y1)
 and (xn,yn)
 are also adjacent.
#define int long long
#define endl '\n'
#define P complex<int>
#define X real()
#define Y imag()

const int INF = 1e9 + 7;

int cross(P a, P b, P c) {
    P u = b - a;
    P v = c - a;
    int cp = (conj(u)*v).Y;
    return (cp > 0) - (cp < 0);
}

bool comp(const P &a, const P &b) {
    return (a.X == b.X) ? (a.Y < b.Y) : (a.X < b.X);
}

bool mid(P a, P b, P c) {
    vector<P> v = {a, b, c};
    sort(v.begin(), v.end(), comp);
    return (v[1] == c);
}

bool check(P a, P b, P c, P d) {
    int cp1 = cross(a, b, c);
    int cp2 = cross(a, b, d);
    int cp3 = cross(c, d, a);
    int cp4 = cross(c, d, b);
    if (cp1 * cp2 < 0 && cp3 * cp4 < 0) return 1;
    if (cp3 == 0 && mid(c, d, a) && cp4 < 0) return 1;
    if (cp4 == 0 && mid(c, d, b) && cp3 < 0) return 1;
    return 0;
}


signed main(){
    int n, m; cin >> n >> m;
    vector<P> v;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v.push_back({x, y});
    }
    v.push_back(v[0]);
    while (m--) {
        int x, y; cin >> x >> y;
        P a = {x, y};
        P b = {INF, INF};
        int cnt = 0;
        int flag = 0;
        for (int i = 0; i < n; i++) {
            int cp = cross(v[i], v[i+1], a);
            if (cp == 0 && mid(v[i], v[i+1], a)) {
                flag = 1;
                break;
            }
            cnt += check(v[i], v[i+1], a, b);
        }
        if (flag) cout << "BOUNDARY" << endl;
        else cout << (cnt & 1 ? "INSIDE" : "OUTSIDE") << endl;
    }
}
/**********************************/
8.Given a polygon, your task is to calculate the number of lattice points inside the polygon and on its boundary.
 A lattice point is a point whose coordinates are integers.

The polygon consists of n
 vertices (x1,y1),(x2,y2),…,(xn,yn)
. The vertices (xi,yi)
 and (xi+1,yi+1)
 are adjacent for i=1,2,…,n−1
, and the vertices (x1,y1)
 and (xn,yn)
 are also adjacent.

 #define int long long
#define endl '\n'
#define P complex<int>
#define X real()
#define Y imag()

signed main(){

    //pick's theorem + https://math.stackexchange.com/a/301895/530789
    int n; cin >> n;
    vector<P> v(n);
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[i] = {x, y};
    }
    v.push_back(v[0]);
    int area = 0;
    int b = 0;
    for (int i = 0; i < n; i++) {
        P x = v[i], y = v[i+1];
        area += (conj(x) * y).Y;
        P z = y - x;
        int g = __gcd(z.X, z.Y);
        b += abs(g);
    }
    //2*area = 2*a + b - 2
    int a = abs(area) - b + 2;
    cout << a/2 << ' ' << b;
}
/***************************/

9.There is a line that goes through the points p1=(x1,y1)
 and p2=(x2,y2). There is also a point p3=(x3,y3).Your task is to determine whether p3
 is located on the left or right side of the line or if it touches the line when we are looking from p1 to p2.

#define int long long
#define endl '\n'

signed main(){
    int t; cin>>t;
    while (t--) {
        int x1, y1, x2, y2, x3, y3;
        cin>>x1>>y1>>x2>>y2>>x3>>y3;
        //cross product
        int cp = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
        if (cp < 0) cout<<"RIGHT"<<endl;
        if (cp > 0) cout<<"LEFT"<<endl;
        if (cp == 0) cout<<"TOUCH"<<endl;
    }
}
/***********************************/

10.Given a set of n
 points in the two-dimensional plane, your task is to determine the convex hull of the points.

#define int long long
#define endl '\n'
#define P complex<int>
#define X real()
#define Y imag()

int cross(P &a, P &b, P &c) {
    P u = c - b;
    P v = a - b;
    int cp = (conj(u) * v).Y;
    return (cp > 0) - (cp < 0);
}

vector<P> hull(vector<P> &v) {
    vector<P> ans = {v[0]};
    for (int i = 1; i < v.size(); i++) {
        while (ans.size() > 1) {
            P b = ans.back();
            ans.pop_back();
            P a = ans.back();
            P c = v[i];
            if (cross(a, b, c) != 1) {
                ans.push_back(b);
                break;
            }
        }
        ans.push_back(v[i]);
    }
    return ans;
}

signed main(){
    int n; cin >> n;
    vector<P> v(n);
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v[i] = {x, y};
    }
    sort(v.begin(), v.end(),
         [] (const P &a, const P &b) {
                return (a.X == b.X) ? (a.Y < b.Y) : (a.X < b.X);
        });
    vector<P> v1 = hull(v);

    sort(v.begin(), v.end(),
         [] (const P &a, const P &b) {
                return (a.X == b.X) ? (a.Y > b.Y) : (a.X > b.X);
        });
    vector<P> v2 = hull(v);
    for (int i = 1; i < v2.size(); i++) {
        if (v2[i] == v1[0]) break;
        v1.push_back(v2[i]);
    }
    cout << v1.size() << endl;
    for (auto i: v1)
        cout << i.X << " " << i.Y << endl;
}

/**************************************/
