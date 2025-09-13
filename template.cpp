/*DS*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T> using orset =  tree<T, null_type, less<T>,  rb_tree_tag,   tree_order_statistics_node_update>;
template <typename T, typename V> using ormap = tree<T, V, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*********************/
/*segtree with lz propagation*/
struct node{
     int mn,lz,sum;
} st[1<<19];

const int neutral = inf;

void app(int i,int x,int l2,int r2){
    st[i].mn += x;
    st[i].sum+=x*(r2-l2+1);
    st[i].lz += x;
}
void psh(int i,int l2,int m2,int r2){
    app(2*i,st[i].lz,l2,m2);
    app(2*i+1,st[i].lz,m2+1,r2);
    st[i].lz = 0;
}
void upd(int l1,int x,int i=1,int l2=0,int r2=n-1){
    if(l2==r2){ st[i].mn = x; return; }
    int m2 = (l2+r2)/2;
    psh(i,l2,m2,r2);
    if(l1 <=m2) upd(l1,x,2*i,l2,m2);
    else upd(l1,x,2*i+1,m2+1,r2);
    st[i].mn = min(st[2*i].mn,st[2*i+1].mn);
}

void upd2(int l1,int r1,int x,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1){ app(i,x,l2,r2); return; }
    int m2 = (l2 + r2)/2;
    psh(i,l2,m2,r2);
    if(l1<=m2) upd2(l1,r1,x,2*i,l2,m2);
    if(m2<r1) upd2(l1,r1,x,2*i+1,m2+1,r2);
    st[i].mn = min(st[2*i].mn,st[2*i+1].mn);
}
int qry(int l1,int r1,int i=1,int l2=0,int r2=n-1){
    if(l1<=l2 && r2<=r1) return st[i].mn;
    int m2 = (l2+r2)/2;
    psh(i,l2,m2,r2);
    int left = (l1 <= m2) ? qry(l1,r1,2*i,l2,m2):neutral;
    int right = (m2<r1) ? qry(l1,r1,2*i+1,m2+1,r2):neutral;
    return min(left,right);
}
/************************************/
/*Fenwick tree 1_based*/
template <typename T>
class fenwick {
      public:
      vector<T> fenw;
      int n;
      fenwick(int _n) : n(_n) { fenw.resize(n); }
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

};
/******************************/
/*Trie*/
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
        if(tri[node][y^1]){ node = tri[node][y^1]; res+=(1<<i); }
        else node = tri[node][y];
    }
    return res;
}
/*****************************/
/*Wavelet tree*/
const int MAXN = (int)3e5 + 9;
const int MAXV = (int)1e9 + 9; //maximum value of any element in array
//array values can be negative too, use appropriate minimum and maximum value
struct wavelet_tree {
  int lo, hi;
  wavelet_tree *l, *r;
  int *b, *c, bsz, csz; // c holds the prefix sum of elements
  wavelet_tree() {
    lo = 1;
    hi = 0;
    bsz = 0;
    csz = 0, l = NULL;
    r = NULL;
  }
  void init(int *from, int *to, int x, int y) {
    lo = x, hi = y;
    if(from >= to) return;
    int mid = (lo + hi) >> 1;
    auto f = [mid](int x) {
      return x <= mid;
    };
    b = (int*)malloc((to - from + 2) * sizeof(int));
    bsz = 0;
    b[bsz++] = 0;
    c = (int*)malloc((to - from + 2) * sizeof(int));
    csz = 0;
    c[csz++] = 0;
    for(auto it = from; it != to; it++) {
      b[bsz] = (b[bsz - 1] + f(*it));
      c[csz] = (c[csz - 1] + (*it));
      bsz++;
      csz++;
    }
    if(hi == lo) return;
    auto pivot = stable_partition(from, to, f);
    l = new wavelet_tree();
    l->init(from, pivot, lo, mid);
    r = new wavelet_tree();
    r->init(pivot, to, mid + 1, hi);
  }
  //kth smallest element in [l, r]
  //for array [1,2,1,3,5] 2nd smallest is 1 and 3rd smallest is 2
  int kth(int l, int r, int k) {
    if(l > r) return 0;
    if(lo == hi) return lo;
    int inLeft = b[r] - b[l - 1], lb = b[l - 1], rb = b[r];
    if(k <= inLeft) return this->l->kth(lb + 1, rb, k);
    return this->r->kth(l - lb, r - rb, k - inLeft);
  }
  //count of numbers in [l, r] Less than or equal to k
  int LTE(int l, int r, int k) {
    if(l > r || k < lo) return 0;
    if(hi <= k) return r - l + 1;
    int lb = b[l - 1], rb = b[r];
    return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
  }
  //count of numbers in [l, r] equal to k
  int count(int l, int r, int k) {
    if(l > r || k < lo || k > hi) return 0;
    if(lo == hi) return r - l + 1;
    int lb = b[l - 1], rb = b[r];
    int mid = (lo + hi) >> 1;
    if(k <= mid) return this->l->count(lb + 1, rb, k);
    return this->r->count(l - lb, r - rb, k);
  }
  //sum of numbers in [l ,r] less than or equal to k
  int sum(int l, int r, int k) {
    if(l > r or k < lo) return 0;
    if(hi <= k) return c[r] - c[l - 1];
    int lb = b[l - 1], rb = b[r];
    return this->l->sum(lb + 1, rb, k) + this->r->sum(l - lb, r - rb, k);
  }
  ~wavelet_tree() {
    delete l;
    delete r;
  }
};
/*1-based indexing and init as (a+1,a+n+1)

/*Math*/
/**********************/
const int FACTORIAL = 4100;
template<int modulo>
struct TurInt {
    unsigned x;
    TurInt() : x() { }
    TurInt(signed sig) : x(sig) {  }
    TurInt(signed long long sig) : x(sig%modulo) { }
    TurInt pow(long long p) { TurInt res = 1, a = *this; while (p) { if (p & 1) res *= a; a *= a; p >>= 1; } return res; }
    int norm(unsigned k) { if (!(-modulo <= k && k < modulo)) k %= modulo; if (k < 0) k += modulo; return k; }

    TurInt &operator+=(TurInt that) { if ((x += that.x) >= modulo) x -= modulo; return *this; }
    TurInt &operator-=(TurInt that) { if ((x += modulo - that.x) >= modulo) x -= modulo; return *this; }
    TurInt &operator*=(TurInt that) { x = (unsigned long long)x * that.x % modulo; return *this; }
    TurInt &operator/=(TurInt that) { return (*this) *= that.pow(modulo - 2); }

    TurInt operator+(TurInt that) const { return TurInt(*this) += that; }
    TurInt operator-(TurInt that) const { return TurInt(*this) -= that; }
    TurInt operator*(TurInt that) const { return TurInt(*this) *= that; }
    TurInt operator/(TurInt that) const { return TurInt(*this) /= that; }

    friend istream& operator>>(istream &is, TurInt& a) { long long k; is >> k; a.x = a.norm(k); return is; }
    friend ostream& operator<<(ostream &os, TurInt a) { os << a.x; return os; }

    TurInt inv(){ assert(x != 0); return pow(mod - 2); }
};
typedef TurInt<mod> lint;

vector<lint> _fact;
vector<lint> _invfact;
vector<lint> _inv;

void init(int m) {    /*call*/
    _fact.resize(m + 1);
    _invfact.resize(m + 1);
    _inv.resize(m + 1);

    _fact[0] = 1;
    _invfact[0] = 1;
    _inv[0] = 0;

    for (int i = 1; i <= m; i++) {
        _fact[i] = _fact[i - 1] * i;
    }
    _invfact[m] = _fact[m].inv();
    for (int i = m; i > 1; i--) {
        _invfact[i - 1] = _invfact[i] * i;
        _inv[i] = _invfact[i] * _fact[i - 1];
    }
}
inline lint fact(int m) { return _fact[m]; }
inline lint invfact(int m) {  return _invfact[m]; }
inline lint inv(int m) {   return _inv[m]; }
inline lint C(int n, int m) { assert(n >= m); return fact(n) * invfact(m) * invfact(n - m); }

/******************************/
const int SIEVE = 1000005;
int lowestprime[SIEVE+1];
vector<int> primes;
//bool isprime[SIEVE+1];

void sieve(int m){  /*call*/ // For any number , call upto sqrt(number) is enough
    for (int i=2; i<=m; ++i){
        if (lowestprime[i] == 0){
            lowestprime[i] = i;
            primes.push_back(i);
			//isprime[i] = true;
        }
        for (int j=0; j<(int32_t)primes.size() && primes[j]<=lowestprime[i] && i*primes[j] <= m; j++){
            lowestprime[i*primes[j]] = primes[j];
        }
    }
}
vector<pair<int,int>>factorize(int n){
    int tmp = n;
    vector<pair<int,int>>res;
    for(auto x : primes){
        if(x*x>tmp) break;
        if(tmp%x) continue;
        int p = 0;
        while(tmp%x==0){ tmp/=x, p++;}
        res.push_back({x,p});
    }
    if(tmp>1) res.push_back({tmp,1});
    return res;
}
/*******************************/
vector<vector<lint>> mul(vector<vector<lint>> a, vector<vector<lint>> b) {
    vector<vector<lint>> c(6, vector<lint>(b[0].size()));
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < b[0].size(); j++)
            for ( int k = 0; k < 6; k++)
                (c[i][j] += a[i][k]*b[k][j]);
    return c;
}
vector<vector<lint>> exp(vector<vector<lint>> x, unsigned int y){
    if(y==1) return x;
    vector<vector<lint>> res = exp(x, y/2);
    res = mul(res,res);
    if( y % 2) res = mul(res,x);
    return res;
}
/*************************************/
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1) return;
    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) { a0[i] = a[2*i]; a1[i] = a[2*i+1]; }
    fft(a0, invert);
    fft(a1, invert);
    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) { a[i] /= 2; a[i + n/2] /= 2; }
        w *= wn;
    }
}
vector<int> multiplyPoly(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<int> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
    result.resize(n-1);
    return result;
}
vector<int> multiplyNum(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);
    vector<int> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
    int carry = 0;
    for (int i = 0; i < n; i++){
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    result.resize(n-1);
    return result;
}
/*graph*/
/********************************/
/*LCA*/
int par[N][LOG + 1];
int depth[N],sz[N];

void dfs(int u, int a = 0){
    par[u][0] = a;
    depth[u] = depth[a] + 1;
    sz[u] = 1;
    for(int i=1;i<=LOG;i++){ par[u][i] = par[par[u][i-1]][i-1];}

    for(auto x : e[u]){
        if(x != a){
            dfs(x, u);
            sz[u]+=sz[x];
        }
    }
}
int kth(int u, int k){
    assert(k >= 0);
    for(int i=0;i<=LOG;i++){ if(k & (1 << i)) u = par[i][u]; }
    return u;
}
int lca(int u,int v){
    if(depth[u] < depth[v]) swap(u,v);
    for(int i = LOG; i>=0 ; i--){ if(depth[par[u][i]]>=depth[v]) u = par[u][i]; }
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
/*********************************/
struct DSU {
    vector<int> par, rnk, sz;
    int c;
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) {
        for (int i = 1; i <= n; ++i) par[i] = i;
    }
    inline int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
    inline bool same(int i, int j) { return find(i) == find(j); }
    inline int get_size(int i) { return sz[find(i)]; }
    int count() { return c; } // connected component
    int unite(int i, int j) {
        if ((i = find(i)) == (j = find(j))) return -1;
        else --c;
        if (rnk[i] > rnk[j]) swap(i, j);
        par[i] = j;
        sz[j] += sz[i];
        if (rnk[i] == rnk[j]) rnk[j]++;
        return j;
    }
};
/*********************/
vector<pair<int,int>>adj[N];
int vis[N];
void dik(int s){
    priority_queue<pair<int,int>> q;
    dist[s] = 0;
    q.push({0,s});
    while(!q.empty()){
        int a = q.top().second;
        q.pop();
        if(vis[a]) continue;
        vis[a] = true;
        for(auto u : adj[a]){
            int b = u.first, w = u.second;
            if(dist[a]+w<dist[b]){ dist[b] = dist[a]+w; q.push({-dist[b],b}); }
        }
    }
}
int k;
void dik_for_kth_shortest(int s){
    priority_queue<pair<int,int>> q;
    dist[s][0] = 0;
    q.push({0,s});
    while(!q.empty()){
        int a = q.top().second;
        int d = -q.top().first;
        q.pop();
        if(dist[a][k-1] < d) continue;
        for(auto u : adj[a]){
            int b = u.first, w = u.second;
            if(d + w < dist[b][k-1]){
                dist[b][k-1] = d+w;
                sort(dist[b],dist[b] + k);
                q.push({-(d+w),b});
            }
        }
    }
}
/***********************************/
/*Geometry*/
struct point{
    long long x,y;
};
long long cross_product(point a, point b){ return a.x*b.y-b.x*a.y; }
long long sq_dist(point a, point b){ return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y); }

bool is_inside(long long x, long long y, vector<point>&points){
    point p1 = {points[points.size()-1].x-points[0].x, points[points.size()-1].y-points[0].y};
    point p2 = {points[1].x-points[0].x, points[1].y-points[0].y};
    point pq = {x-points[0].x, y-points[0].y};
    if(!(cross_product(p1, pq)<=0 && cross_product(p2,pq)>=0)) return false;
    int l = 0, r = points.size();
    while (r - l > 1) {
        int mid = (l + r) / 2;
        point cur = {points[mid].x-points[0].x, points[mid].y-points[0].y};
        if (cross_product(cur, pq)<0) { r = mid; }
        else { l = mid; }
    }

    if(l == points.size()-1){ return sq_dist(points[0], {x,y}) <= sq_dist(points[0], points[l]);}
    else{
        point l_l1 = {points[l+1].x-points[l].x, points[l+1].y-points[l].y};
        point lq = {x-points[l].x, y-points[l].y};
        return (cross_product(l_l1,lq) >=0);
    }
}

void pick_p0(vector<point>&points){
    long long min_x=1e9+5;
    long long max_y=-1e9-5;
    int min_i=0;
    for(int i=0;i<points.size();i++){
        if(points[i].x < min_x || (points[i].x == min_x && points[i].y > max_y)){
            min_x=points[i].x;
            max_y=points[i].y;
            min_i = i;
        }
    }

    rotate(points.begin(), points.begin() + min_i, points.end());
}
/*string*/
struct manacher{
    vector<int>p; // p denotes the i'th center's longest pallindrome on both side
    void run_manacher(string s){
        int n = s.length();
        p.assign(n,1);
        int l = 1, r = 1;
        for(int i=1;i<n;i++){
            p[i] = max(0LL, min(r-i,p[l+r-i]));
            while(i+p[i]<n && i-p[i]>=0 && s[i+p[i]]==s[i-p[i]]) p[i]++;
            if(i+p[i] > r) l = i - p[i] , r = i + p[i];
        }
    }
    void build(string s){
        string t;
        for(auto x : s){ t += string("#") + x; }
        run_manacher(t + "#");
    }
    //odd -> at chars, else at gaps after that index
    inline void show(){ cout << p << '\n'; }
    inline int longest(int center,bool odd){ return p[2*center + 1 + (!odd)] - 1; }
    inline bool check(int l,int r){ return ((r-l+1)<=longest((l+r)/2,l%2==r%2)); }
};
/************************************/
// returns the longest proper prefix array of pattern p
// where lps[i]=longest proper prefix which is also suffix of p[0...i]
vector<int> build_lps(string p) {
  int sz = p.size();
  vector<int> lps;
  lps.assign(sz + 1, 0);
  int j = 0;
  lps[0] = 0;
  for(int i = 1; i < sz; i++) {
    while(j >= 0 && p[i] != p[j]) {
      if(j >= 1) j = lps[j - 1];
      else j = -1;
    }
    j++;
    lps[i] = j;
  }
  return lps;
}
vector<int>ans;
// returns matches in vector ans in 0-indexed
void kmp(vector<int> lps, string s, string p) {
  int psz = p.size(), sz = s.size();
  int j = 0;
  for(int i = 0; i < sz; i++) {
    while(j >= 0 && p[j] != s[i])
      if(j >= 1) j = lps[j - 1];
      else j = -1;
    j++;
    if(j == psz) {
      j = lps[j - 1];
      // pattern found in string s at position i-psz+1
      ans.push_back(i - psz + 1);
    }
    // after each loop we have j=longest common suffix of s[0..i] which is also prefix of p
  }
}
/*call build then kmp.. if ans is empty then no matching substring*/
/****************************************/







