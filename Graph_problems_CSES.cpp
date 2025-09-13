/*CSES*/
/*Advanced*/
1. You are given an array of n
numbers. In how many ways can you choose a subset of the numbers with sum x?
    int n,x;
    cin >> n >> x;
    vector<int>a(n); cin >> a;
    vector<int>v1,v2;
    for(int i=0;i<(1 << (n/2));i++){
        int s = 0;
        for(int j = 0;j<n/2;j++){
            if(i & (1 << j)) s+=a[j];
        }
        v1.push_back(s);
    }
    for(int i=0;i<(1 << ((n+1)/2));i++){
        int s = 0;
        for(int j = 0;j<(n+1)/2;j++){
            if(i & ( 1 << j)) s+=a[n/2 + j];
        }
        v2.push_back(s);
    }
    sort(all(v1));
    sort(all(v2));
    int res = 0;
    for(auto v : v1){
        auto it = lower_bound(all(v2),x-v)-v2.begin();
        auto it2 = upper_bound(all(v2),x-v)-v2.begin();
        res+=(it2 - it);
    }
    cout << res << '\n';

/*********************/
2. The Hamming distance between two strings a
 and b of equal length is the number of positions where the strings differ.
You are given n bit strings, each of length k
 and your task is to calculate the minimum Hamming distance between two strings.
    int n,k; cin>>n>>k;
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) {
    	string s; cin>>s;
    	reverse(s.begin(), s.end());
    	for (int j = 0; j < s.size(); j++) {
    		v[i] += (s[j] == '1')*(1<<j);
    	}
    }
    int ans = 32;
    for (int i = 0; i < n; i++) {
    	for (int j = i+1; j < n; j++) {
    		ans = min(ans, (int) __builtin_popcount(v[i]^v[j]));
    	}
    }
    cout<<ans;
/**********************************/
3. A directed acyclic graph consists of n
 nodes and m edges. The nodes are numbered 1,2,…,n.
Calculate for each node the number of nodes you can reach from that node (including the node itself).

int N, M, a, b, in[maxN];
bitset<maxN> ans[maxN];
vector<int> G[maxN];
queue<int> Q;

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        G[b].push_back(a);
        in[a]++;
    }

    for(int i = 1; i <= N; i++){
        if(in[i] == 0){
            ans[i].set(i);
            Q.push(i);
        }
    }

    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int v : G[u]){
            ans[v] |= ans[u];
            in[v]--;
            if(in[v] == 0){
                ans[v].set(v);
                Q.push(v);
            }
        }
    }

    for(int i = 1; i <= N; i++)
        printf("%d%c", (int) ans[i].count(), (" \n")[i==N]);
}

/**************************************/
4. A directed graph consists of n
 nodes and m edges. The edges are numbered 1,2,…,n .
Your task is to answer q queries of the form "can you reach node b from node a ?"

const int mxN = 5e4+5;
vector<bitset<mxN>> dp(mxN);
vector<int> adj[mxN], adj2[mxN], cond[mxN];
vector<int> v;
int comp[mxN];
int cnt = 0;
int vis[mxN];

void dfs(int s, vector<int> adj[]) {
    if (vis[s]) return;
    vis[s] = 1;
    for (auto i: adj[s])
        dfs(i, adj);
    v.push_back(s);
}

void dfs2(int s, int cnt) {
    if (comp[s]) return;
    comp[s] = cnt;
    for (auto i: adj2[s])
        dfs2(i, cnt);
}



signed main(){
    int n, m, t; cin >> n >> m >> t;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj2[y].push_back(x);
    }
    //topological sort
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i, adj);
    }
    //condensing SCCs
    reverse(v.begin(), v.end());
    for (auto i: v) {
        if (!comp[i]) {
            dfs2(i, ++cnt);
        }
    }
    //condesed graph.
    for (int i = 1; i <= n; i++) {
        for (auto j: adj[i]) if (comp[i] != comp[j]) {
            cond[comp[i]].push_back(comp[j]);
        }
    }

    memset(vis, 0, sizeof vis);
    v.clear();
    //topological sort of condensed graphs
    for (int i = 1; i <= cnt; i++) {
        if (!vis[i])
            dfs(i, cond);
    }

    for (auto s: v) {
        dp[s][s] = 1;
        for (auto i: cond[s])
            dp[s] |= dp[i];
    }

    while (t--) {
        int x, y; cin >> x >> y;
        cout << (dp[comp[x]][comp[y]] ? "YES" : "NO") << endl;
    }

}

/********************************/
5.Given a string, your task is to process operations where you cut a substring and paste it to the end of the string.
What is the final string after all the operations?

struct node {
    node *left, *right;
    int weight, size;
    char value;
    node(char v) {
        left = right = NULL;
        weight = rand();
        size = 1;
        value = v;
    }
};

int size(node *treap) {
    if (treap == NULL) return 0;
    return treap->size;
}

void split(node *treap, node *&left, node *&right, int k) {
    if (treap == NULL) {
        left = right = NULL;
    }
    else {
        if (size(treap->left) < k) {
            split(treap->right, treap->right, right, k - size(treap->left)-1);
            left = treap;
        }
        else {
            split(treap->left, left, treap->left, k);
            right = treap;
        }
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

void merge(node *&treap, node *left, node *right) {
    if (left == NULL) treap = right;
    else if(right == NULL) treap = left;
    else {
        if (left->weight < right->weight) {
            merge(left->right, left->right, right);
            treap = left;
        }
        else {
            merge(right->left, left, right->left);
            treap = right;
        }
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

void print(node *treap) {
    if (treap == NULL) return;
    print(treap->left);
    cout << treap->value;
    print(treap->right);
}


signed main(){
    node *treap = 0;
    int n, m; cin >> n >> m;
    string s; cin >> s;
    for (auto i: s) {
        merge(treap, treap, new node(i));
    }

    while (m--) {
        int x, y; cin >> x >> y;
        node *A, *B, *C, *D;
        split(treap, A, B, x - 1);
        split(B, D, C, y - x + 1);
        merge(treap, A, C);
        merge(treap, treap, D);
    }
    print(treap);
}

/************************************/
6.Given a string, your task is to process operations where you reverse a substring of the string.
 What is the final string after all the operations?

struct node {
    node *L, *R;
    int W, S;
    char V;
    bool F;
    node(char x) {
        L = R = 0;
        W = rand();
        S = 1;
        V = x;
        F = 0;
    }
};

int size(node *treap) {
    return (treap == 0 ? 0 : treap->S);
}

void push(node *treap) {
    if (treap && treap->F) {
        treap->F = 0;
        swap(treap->L, treap->R);
        if (treap->L) treap->L->F ^= 1;
        if (treap->R) treap->R->F ^= 1;
    }
}

void split(node *treap, node *&left, node *&right, int k) {
    if (treap == 0)
        left = right = 0;
    else {
        push(treap);
        if (size(treap->L) < k) {
            split(treap->R, treap->R, right, k - size(treap->L) - 1);
            left = treap;
        }
        else {
            split(treap->L, left, treap->L, k);
            right = treap;
        }
        treap->S = size(treap->L) + size(treap->R) + 1;
    }
}

void merge(node *&treap, node *left, node *right) {
    if (left == 0) treap = right;
    else if (right == 0) treap = left;
    else {
        push(left);
        push(right);
        if (left->W < right->W) {
            merge(left->R, left->R, right);
            treap = left;
        }
        else {
            merge(right->L, left, right->L);
            treap = right;
        }
        treap->S = size(treap->L) + size(treap->R) + 1;
    }
}

void print(node *treap) {
    if (treap == NULL) return;
    push(treap);
    print(treap->L);
    cout << treap->V;
    print(treap->R);
}


signed main(){
    node *treap = 0;
    int n, m; cin >> n >> m;
    string s; cin >> s;
    for (auto i: s) {
        merge(treap, treap, new node(i));
    }
    while (m--) {
        int x, y; cin >> x >> y;
        node *A, *B, *C;
        split(treap, A, B, x - 1);
        split(B, B, C, y - x + 1);
        B->F ^= 1;
        merge(treap, A, B);
        merge(treap, treap, C);
    }
    print(treap);
}
/*************************************/
7. Given an array of n integers, you have to process following operations:
 1. reverse a subarray
 2. calculate the sum of values in a subarray

struct node {
    node *L, *R;
    int W, S, sm, V;
    bool F;
    node(int x) {
        L = R = 0;
        W = rand();
        S = 1;
        sm = x;
        V = x;
        F = 0;
    }
};

int size(node *treap) {
    return (treap == 0 ? 0 : treap->S);
}

int sum(node *treap) {
    return (treap == 0 ? 0 : treap->sm);
}

void push(node *treap) {
    if (treap && treap->F) {
        treap->F = 0;
        swap(treap->L, treap->R);
        if (treap->L) treap->L->F ^= 1;
        if (treap->R) treap->R->F ^= 1;
    }
}

void split(node *treap, node *&left, node *&right, int k) {
    if (treap == 0)
        left = right = 0;
    else {
        push(treap);
        if (size(treap->L) < k) {
            split(treap->R, treap->R, right, k - size(treap->L) - 1);
            left = treap;
        }
        else {
            split(treap->L, left, treap->L, k);
            right = treap;
        }
        treap->S = size(treap->L) + size(treap->R) + 1;
        treap->sm = sum(treap->L) + sum(treap->R) + treap->V;
    }
}

void merge(node *&treap, node *left, node *right) {
    if (left == 0) treap = right;
    else if (right == 0) treap = left;
    else {
        push(left);
        push(right);
        if (left->W < right->W) {
            merge(left->R, left->R, right);
            treap = left;
        }
        else {
            merge(right->L, left, right->L);
            treap = right;
        }
        treap->S = size(treap->L) + size(treap->R) + 1;
        treap->sm = sum(treap->L) + sum(treap->R) + treap->V;
    }
}

int find_sum(node *treap, int k) {
    if (treap == 0 || k == 0)
        return 0;
    else {
        push(treap);
        if (size(treap->L) < k) {
            return sum(treap->L) + treap->V + find_sum(treap->R, k - size(treap->L) - 1);
        }
        else {
            return find_sum(treap->L, k);
        }
    }
}

signed main(){
    node *treap = 0;
    int n, m; cin >> n >> m;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        merge(treap, treap, new node(x));
    }

    while (m--) {
        int ch; cin >> ch;
        if (ch == 1) {
            int x, y; cin >> x >> y;
            node *A, *B, *C;
            split(treap, A, B, x - 1);
            split(B, B, C, y - x + 1);
            B->F ^= 1;
            merge(treap, A, B);
            merge(treap, treap, C);
        }
        else {
            int x, y; cin >> x >> y;
            cout << find_sum(treap, y) - find_sum(treap, x-1) << endl;
        }
    }
}

/*******************************/
8.There are n cities and m roads between them. There is a route between any two cities.
A road is called necessary if there is no route between some two cities after removing that road.
Your task is to find all necessary roads.
vector<int> adj[mxN];
vector<pair<int,int>> ans;
int vis[mxN], low[mxN];
int cnt = 0;

void dfs(int s, int p) {
    vis[s] = ++cnt;
    low[s] = vis[s];
    for (auto i: adj[s]) {
        if (i != p) {
            if (vis[i]) //back edge
                low[s] = min(low[s], vis[i]);
            else {
                dfs(i, s);
                low[s] = min(low[s], low[i]);
                if (low[i] > vis[s])
                    ans.push_back({s, i});
            }
        }
    }
}

signed main(){
    int n,m; cin>>n>>m;
    for (int i = 0; i < m; i++) {
        int x, y; cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i, 0);
    }
    cout<<ans.size()<<endl;
    for (auto [i, j]: ans)
        cout<<i<<' '<<j<<endl;
}

/***************************************/
9. There are n cities and m roads between them. There is a route between any two cities.
A city is called necessary if there is no route between some other two cities after removing that city (and adjacent roads).
Your task is to find all necessary cities.

vector<int> adj[mxN];
int ans[mxN];
int vis[mxN], low[mxN];
int cnt = 0;

void dfs(int s, int p) {
    vis[s] = ++cnt;
    low[s] = vis[s];
    int ch = 0; //children connected with tree-edge
    for (auto i: adj[s]) {
        if (i != p) {
            if (vis[i]) //back edge
                low[s] = min(low[s], vis[i]);
            else {
                dfs(i, s);
                low[s] = min(low[s], low[i]);
                if (p != 0 && low[i] >= vis[s])
                    ans[s] = 1;
                ch++;
            }
        }
    }
    if (p == 0 && ch > 1)
        ans[s] = 1;
}

signed main(){
    int n, m; cin>>n>>m;
    for (int i = 0; i < m; i++) {
        int x, y; cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs(i, 0);
    }
    cout<<accumulate(ans, ans+n+1, 0)<<endl;
    for (int i = 1; i <= n; i++) if (ans[i])
        cout<<i<<' ';
}
/*******************************/
10. You are given an undirected graph that has n nodes and m edges.
We consider subgraphs that have all nodes of the original graph and some of its edges.
A subgraph is called Eulerian if each node has even degree.

Your task is to count the number of Eulerian subgraphs modulo 109+7.

const int mxN = 1e5+5;
const int md = 1e9+7;
vector<int> adj[mxN];
int vis[mxN];

int exp(int x, int y, int md){
    int ans = 1;
    x = x%md;
    while (y > 0) {
        if (y&1)
            ans = ans*x%md;
        y = y>>1;
        x = x*x%md;
    }
    return ans;
}

int cnt = 0;
void dfs(int s, int p) {
    if (vis[s]) return;
    vis[s] = 1;
    for (auto i: adj[s]) if (i != p) {
        if (vis[i] == 1)
            cnt++;
        else if (vis[i] == 0)
            dfs(i, s);
    }
    vis[s] = 2;
}

signed main(){
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int ans = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            cnt = 0;
            dfs(i, 0);
            ans = ans * exp(2, cnt, md) % md;
        }
    }

    cout << ans;
}
/******************************************/
11. You are playing a game that consists of n levels.
 Each level has a monster. On levels 1 to n-1,you can either kill or escape the monster. However, on level n
 you must kill the final monster to win the game.
Killing a monster takes sf time where s is the monster strength and f is your skill factor (lower skill factor is better).
After killing a monster, you get a new skill factor.What is the minimum total time in which you can win the game?

signed main() {
    int n, k; cin >> n >> k;
    vector<pair<int, int>> S = {{k, 0}};
    vector<int> v = {1};
    int s[n], f[n];
    for (auto &i: s) cin >> i;
    for (auto &i: f) cin >> i;
    int c = 0;
    for (int i = 0; i < n; i++) {
        int x = s[i];
        int it = upper_bound(v.begin(), v.end(), x) - v.begin() - 1;
        int m = f[i];
        c = x*S[it].F + S[it].S;
        if (S.back().F == m) continue; // if same slope then always bad line
        while (S.size() >= 2) {
            auto y2 = S[S.size() - 1];
            auto y3 = S[S.size() - 2];
            if ((y2.S - c)*(m - y3.F) < (y3.S - c)*(m - y2.F)) {
                S.pop_back();
                v.pop_back();
            }
            else break;
        }
        int x1 = ceil((S.back().S - c)*1.0/(m - S.back().F));
        v.push_back(x1);
        S.push_back({m, c});
    }
    cout << c;
}
/*******************************/
12. Given an array of n elements, your task is to divide into k subarrays.
The cost of each subarray is the square of the sum of the values in the subarray.
What is the minimum total cost if you act optimally?

const int mxN = 3005;
int a[mxN], pre[mxN];
vector<int> dp_prev(mxN), dp_cur(mxN);
const int INF = 1LL<<60;

int cost(int l, int r) {
    return (pre[r] - pre[l-1]) * (pre[r] - pre[l-1]);
}

void solve(int a, int b, int x, int y) {
    if (a > b)
        return;
    int m = (a + b) / 2;
    pair<int, int> p = {INF, -1};
    for (int i = x; i <= min(m, y); i++) {
        p = min(p, {dp_prev[i] + cost(i+1, m), i});
    }
    dp_cur[m] = p.first;
    solve(a, m-1, x, p.second);
    solve(m+1, b, p.second, y);
}

signed main(){
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i+1] = pre[i] + a[i];
    }

    for (int i = 1; i <= n; i++)
        dp_prev[i] = cost(1, i);

    for (int i = 2; i <= k; i++) {
        solve(1, n, 1, n);
        dp_prev = dp_cur;
    }
    cout << dp_prev[n];
}
/**********************************/

13. There are n houses on a street numbered 1 to n. The distance of houses a and b is abs(a−b).
You know the number of children in each house. Your task is to establish k
schools in such a way that each school is in some house. Then, each child goes to the nearest school.
What is the minimum total walking distance of the children if you act optimally ?

const int mxN = 3005;
int a[mxN], pre[3][mxN];
int dp[mxN][mxN]; //dp[i][j] = min cost for j divisions with 1 school at i.
const int INF = 1LL<<60;
int n;

int cost(int a, int b) {
    int m = (a+b)/2;
    int ans = (pre[1][m] - pre[1][a-1]) - a*(pre[0][m] - pre[0][a-1]);
    ans += (pre[2][b] - pre[2][m]) - (n-b+1)*(pre[0][b] - pre[0][m]);
    return ans;
}

void solve(int j, int a, int b, int x, int y) {
    if (a > b)
        return;
    int m = (a + b) / 2;
    pair<int, int> p = {INF, -1};
    for (int i = x; i <= min(m, y); i++) {
        p = min(p, {dp[i][j-1] + cost(i, m), i});
    }
    dp[m][j] = p.first;
    solve(j, a, m-1, x, p.second);
    solve(j, m+1, b, p.second, y);
}

signed main(){
    int k; cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[0][i+1] = pre[0][i] + a[i];
        pre[1][i+1] = pre[1][i] + (i+1)*a[i];
        pre[2][i+1] = pre[2][i] + (n-i)*a[i];
    }

    for (int i = 1; i <= n; i++)
        dp[i][1] = (pre[2][i] - pre[2][0]) - (n-i+1)*(pre[0][i] - pre[0][0]);

    for (int i = 2; i <= k; i++) {
        solve(i, 1, n, 1, n);
    }
    int ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[i][k] + (pre[1][n] - pre[1][i-1]) - i*(pre[0][n] - pre[0][i-1]));
    }
    cout << ans;
}
/******************************/

14. Given an array of n numbers, your task is to divide it into n subarrays, each of which has a single element.
On each move, you may choose any subarray and split it into two subarrays.
The cost of such a move is the sum of values in the chosen subarray.
What is the minimum total cost if you act optimally?

const int mxN = 5e3+5;
pair<int, int> dp[mxN][mxN];
int pre[mxN];
const int INF = 1LL<<60;

signed main(){
    int n; cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        pre[i] = pre[i-1] + x;
    }
    for (int i = 1; i < n; i++) {
        dp[i][i+1] = {pre[i+1] - pre[i-1], i};
    }

    for (int k = 3; k <= n; k++) {
        for (int i = 1; i+k-1 <= n; i++) {
            int j = i+k-1;
            pair<int, int> p = {dp[i][j-1].second, dp[i+1][j].second};
            dp[i][j] = {INF, -1};
            for (int x = p.first; x <= p.second; x++) {
                dp[i][j] = min(dp[i][j], {dp[i][x].first + dp[x+1][j].first, x});
            }
            dp[i][j].first += pre[j] - pre[i-1];
        }
    }
    cout << dp[1][n].first;

}
15. You are given a binary string of length n
 and your task is to calculate for every k between 1…n−1
 the number of ways we can choose two positions i and j
 such that i−j=k and there is a one-bit at both positions.

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiplyPoly(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());

    result.resize(n-1);
    return result;
}

vector<int> multiplyNum(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());


    int carry = 0;
    for (int i = 0; i < n; i++){
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }

    result.resize(n-1);
    return result;
}


void solution(){
    string s;
    cin >> s;
    int n = s.size();
    vector<int>a(n),b(n);
    for(int i=0;i<n;i++){
        if(s[i]=='1'){
            a[i] = 1;
            b[n-i-1] = 1;
        }
    }
    auto res = multiplyPoly(a,b);
    for(int i=0;i<n-1;i++){
        cout << res[n+i] << ' ';
    }
}
/****************************************/

16. Consider an undirected graph that consists of n
nodes and m edges. There are two types of events that can happen:
A new edge is created between nodes a and b.
An existing edge between nodes a and b is removed.
Your task is to report the number of components after every event.

typedef pair<int,int> pii;
typedef array<int,3> triple;
const int maxN = 1e5+1;
const int SIZE = 3e5+1;
const int INF = 0x3f3f3f3f;

int N, M, K, root, components, del_time[SIZE];
bool used[SIZE];
pii edges[SIZE];
triple ops[maxN];
map<pii,deque<int>> edge_id_map;

struct Node {
    bool rev = false;
    Node *c[2] = {nullptr, nullptr}, *p = nullptr;
    int mn, id;

    Node(int i){
        mn = id = i;
    }

    void push(){
        if(rev){
            swap(c[0], c[1]);
            if(c[0])    c[0]->rev ^= true;
            if(c[1])    c[1]->rev ^= true;
            rev = false;
        }
    }

    void pull(){
        mn = id;
        for(int i = 0; i < 2; i++)
            if(c[i] && del_time[c[i]->mn] < del_time[mn])
                mn = c[i]->mn;
    }
} *LCT[SIZE];

bool notRoot(Node *t){
    return t->p && (t->p->c[0] == t || t->p->c[1] == t);
}

void rotate(Node *t){
    Node *p = t->p;
    bool b = (p->c[0] == t);
    if((t->p = p->p) && notRoot(p)) t->p->c[(t->p->c[1] == p)] = t;
    if((p->c[!b]=t->c[b]))          p->c[!b]->p = p;
    t->c[b] = p;
    p->p = t;
    p->pull();
}


void splay(Node *t){
    while(notRoot(t)){
        Node *p = t->p;
        p->push();
        t->push();
        rotate(t);
    }
    t->push();
    t->pull();
}

Node* access(Node *t){
    Node *last = nullptr;
    for(Node *u = t; u; u = u->p){
        splay(u);
        u->c[1] = last;
        last = u;
    }
    splay(t);
    return last;
}

void evert(Node *t){
    access(t);
    t->rev = true;
}

void link(Node *u, Node *v){
    evert(u);
    u->p = v;
}

void cut(Node *u, Node *v){
    evert(u);
    access(v);
    if(v->c[0]) v->c[0]->p = 0;
    v->c[0] = 0;
    v->pull();
}

Node* path(Node *u, Node *v){
    evert(u);
    access(v);
    return v;
}

bool connected(Node *u, Node *v){
    path(u, v);
    while(v->c[0])
        v = v->c[0];
    return u == v;
}

void create_edge(int u, int v){
    int id = edge_id_map[{u, v}].front();
    if(!connected(LCT[u], LCT[v])){
        components--;
        link(LCT[id], LCT[u]);
        link(LCT[id], LCT[v]);
        used[id] = true;
    } else {
        int mn = path(LCT[u], LCT[v])->mn;
        if(del_time[mn] < del_time[id]){
            int cu = edges[mn].first;
            int cv = edges[mn].second;
            cut(LCT[mn], LCT[cu]);
            cut(LCT[mn], LCT[cv]);
            used[mn] = false;
            link(LCT[id], LCT[u]);
            link(LCT[id], LCT[v]);
            used[id] = true;
        }
    }
}

void destroy_edge(int u, int v){
    int id = edge_id_map[{u, v}].front();
    edge_id_map[{u, v}].pop_front();
    if(!used[id])   return;
    cut(LCT[id], LCT[u]);
    cut(LCT[id], LCT[v]);
    used[id] = false;
    components++;
}

int main(){
    scanf("%d %d %d", &N, &M, &K);

    root = 1;
    for(int i = 1; i <= N; i++){
        LCT[i] = new Node(i);
        del_time[i] = INF;
    }

    for(int i = 1, a, b; i <= M; i++){
        scanf("%d %d", &a, &b);
        if(a > b)   swap(a, b);
        edges[N+i] = {a, b};
        del_time[N+i] = INF;
        LCT[N+i] = new Node(N+i);
        edge_id_map[{a, b}].push_back(N+i);
    }

    for(int i = 1, t, a, b; i <= K; i++){
        scanf("%d %d %d", &t, &a, &b);
        if(a > b)   swap(a, b);
        ops[i] = {t, a, b};
        edges[N+M+i] = {a, b};

        if(t == 2){
            int id = edge_id_map[{a, b}].back();
            del_time[id] = i;
        } else {
            del_time[N+M+i] = INF;
            LCT[N+M+i] = new Node(N+M+i);
            edge_id_map[{a, b}].push_back(N+M+i);
        }
    }

    components = N;
    for(int i = N+1; i <= N+M; i++){
        int u = edges[i].first;
        int v = edges[i].second;
        create_edge(u, v);
    }
    printf("%d ", components);

    for(int i = 1; i <= K; i++){
        int t = ops[i][0];
        int u = ops[i][1];
        int v = ops[i][2];
        if(t == 1)  create_edge(u, v);
        else        destroy_edge(u, v);
        printf("%d%c", components, (" \n")[i==K]);
    }
}
/*****************************************/
17. There are n cities and m routes through which parcels can be carried from one city to another city.
For each route, you know the maximum number of parcels and the cost of a single parcel.
You want to send k parcels from Syrjälä to Lehmälä. What is the cheapest way to do that?

using namespace std;
typedef long long ll;
const int maxN = 501, maxM = 1001;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int N, M, K, p[maxN];
ll d[maxN], cap[maxN][maxN], cost[maxN][maxN];
bool inq[maxN];
vector<int> G[maxN];

struct Edge {
    int u, v;
    ll r, c;
} edges[maxM], redges[maxM];

void bellman_ford(){
    fill(inq+1, inq+N+1, false);
    fill(d+1, d+N+1, INF);
    fill(p+1, p+N+1, 0);

    queue<int> Q;
    Q.push(1);
    d[1] = 0;
    inq[1] = true;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        inq[u] = false;

        for(int i : G[u]){
            Edge e = (i < 0 ? redges[-i] : edges[i]);
            if(e.r > 0 && d[e.v] > d[u] + e.c){
                d[e.v] = d[u] + e.c;
                p[e.v] = i;
                if(!inq[e.v]){
                    inq[e.v] = true;
                    Q.push(e.v);
                }
            }
        }
    }
}

ll minimum_cost_flow(){
    ll flow = 0, cost = 0;
    while(flow < K){
        bellman_ford();
        if(d[N] == INF) break;

        ll aug = K-flow;
        int u = N;
        while(u != 1){
            Edge e = (p[u] < 0 ? redges[-p[u]] : edges[p[u]]);
            aug = min(aug, e.r);
            u = e.u;
        }

        flow += aug;
        cost += aug * d[N];
        u = N;
        while(u != 1){
            if(p[u] < 0){
                redges[-p[u]].r -= aug;
                edges[-p[u]].r += aug;
            } else {
                redges[p[u]].r += aug;
                edges[p[u]].r -= aug;
            }
            u = (p[u] < 0 ? redges[-p[u]].u : edges[p[u]].u);
        }
    }
    return (flow < K ? -1 : cost);
}

int main(){
    scanf("%d %d %d", &N, &M, &K);
    for(int i = 1, u, v, r, c; i <= M; i++){
        scanf("%d %d %d %d", &u, &v, &r, &c);
        G[u].push_back(i);
        G[v].push_back(-i);
        edges[i] = {u, v, r, c};
        redges[i] = {v, u, 0, -c};
    }
    printf("%lld\n", minimum_cost_flow());
}
/*****************************************/
18. A company has n employees and there are n tasks that need to be done. We know for each employee the cost of carrying out each task.
Every employee should be assigned to exactly one task.
What is the minimum total cost if we assign the tasks optimally and how could they be assigned?

using namespace std;
typedef long long ll;
const int maxN = 402, maxM = 40401;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int N, p[maxN];
ll d[maxN], cap[maxN][maxN], cost[maxN][maxN];
bool inq[maxN], vis[maxM];
vector<int> path, G[maxN];

struct Edge {
    int u, v;
    ll r, c;
} edges[maxM], redges[maxM];

void bellman_ford(int start = 0){
    fill(inq, inq+maxN, false);
    fill(d, d+maxN, INF);
    fill(p, p+maxN, 0);

    queue<int> Q;
    Q.push(start);
    d[start] = 0;
    inq[start] = true;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        inq[u] = false;

        for(int i : G[u]){
            Edge e = (i < 0 ? redges[-i] : edges[i]);
            if(e.r > 0 && d[e.v] > d[u] + e.c){
                d[e.v] = d[u] + e.c;
                p[e.v] = i;
                if(!inq[e.v]){
                    inq[e.v] = true;
                    Q.push(e.v);
                }
            }
        }
    }
}

ll minimum_cost_flow(){
    ll flow = 0, cost = 0;
    while(flow < N){
        bellman_ford();
        if(d[2*N+1] == INF) break;

        ll aug = N-flow;
        int u = 2*N+1;
        while(u != 0){
            Edge e = (p[u] < 0 ? redges[-p[u]] : edges[p[u]]);
            aug = min(aug, e.r);
            u = e.u;
        }

        flow += aug;
        cost += aug * d[2*N+1];
        u = 2*N+1;
        while(u != 0){
            if(p[u] < 0){
                redges[-p[u]].r -= aug;
                edges[-p[u]].r += aug;
            } else {
                redges[p[u]].r += aug;
                edges[p[u]].r -= aug;
            }
            u = (p[u] < 0 ? redges[-p[u]].u : edges[p[u]].u);
        }
    }
    return (flow < N ? -1 : cost);
}

void dfs(int u = 0){
    if(u == 2*N+1)  return;
    if(u != 0)      path.push_back(u);
    for(int i : G[u]){
        if(i > 0 && edges[i].r == 0 && !vis[i]){
            vis[i] = true;
            dfs(edges[i].v);
            return;
        }
    }
}

int main(){
    scanf("%d", &N);
    int edgeID = 1;
    for(int u = 1; u <= N; u++){
        for(int v = N+1, c; v <= 2*N; v++){
            scanf("%d", &c);
            G[u].push_back(edgeID);
            G[v].push_back(-edgeID);
            edges[edgeID] = {u, v, 1, c};
            redges[edgeID] = {v, u, 0, -c};
            edgeID++;
        }
    }
    for(int v = 1; v <= N; v++){
        G[0].push_back(edgeID);
        G[v].push_back(-edgeID);
        edges[edgeID] = {0, v, 1, 0};
        redges[edgeID] = {v, 0, 0, 0};
        edgeID++;
    }
    for(int u = N+1; u <= 2*N; u++){
        G[u].push_back(edgeID);
        G[2*N+1].push_back(-edgeID);
        edges[edgeID] = {u, 2*N+1, 1, 0};
        redges[edgeID] = {2*N+1, u, 0, 0};
        edgeID++;
    }

    printf("%lld\n", minimum_cost_flow());
    for(int i = 0; i < N; i++){
        path.clear();
        dfs();
        printf("%d %d\n", path[0], path[1]-N);
    }
}
/**********************************************/
19. A game consists of nrooms and m teleporters. At the beginning of each day, you start in room 1
and you have to reach room n. You can use each teleporter at most once during the game.
You want to play the game for exactly k
days. Every time you use any teleporter you have to pay one coin. What is the minimum number of coins you have to pay during k
days if you play optimally?

using namespace std;
const int maxN = 501, maxM = 1001;
const int INF = 0x3f3f3f3f;

int N, M, K, p[maxN], d[maxN];
bool inq[maxN], vis[maxM];
vector<int> path, G[maxN];

struct Edge {
    int u, v, r, c;
} edges[maxM], redges[maxM];

void bellman_ford(){
    fill(inq+1, inq+N+1, false);
    fill(d+1, d+N+1, INF);
    fill(p+1, p+N+1, 0);

    queue<int> Q;
    Q.push(1);
    d[1] = 0;
    inq[1] = true;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        inq[u] = false;

        for(int i : G[u]){
            Edge e = (i < 0 ? redges[-i] : edges[i]);
            if(e.r > 0 && d[e.v] > d[u] + e.c){
                d[e.v] = d[u] + e.c;
                p[e.v] = i;
                if(!inq[e.v]){
                    inq[e.v] = true;
                    Q.push(e.v);
                }
            }
        }
    }
}

int minimum_cost_flow(){
    int flow = 0, cost = 0;
    while(flow < K){
        bellman_ford();
        if(d[N] == INF) break;

        int aug = K-flow;
        int u = N;
        while(u != 1){
            Edge e = (p[u] < 0 ? redges[-p[u]] : edges[p[u]]);
            aug = min(aug, e.r);
            u = e.u;
        }

        flow += aug;
        cost += aug * d[N];
        u = N;
        while(u != 1){
            if(p[u] < 0){
                redges[-p[u]].r -= aug;
                edges[-p[u]].r += aug;
            } else {
                redges[p[u]].r += aug;
                edges[p[u]].r -= aug;
            }
            u = (p[u] < 0 ? redges[-p[u]].u : edges[p[u]].u);
        }
    }
    return (flow < K ? -1 : cost);
}

void dfs(int u = 1){
    path.push_back(u);
    if(u == N)  return;
    for(int i : G[u]){
        if(i > 0 && edges[i].r == 0 && !vis[i]){
            vis[i] = true;
            dfs(edges[i].v);
            return;
        }
    }
}

int main(){
    scanf("%d %d %d", &N, &M, &K);
    for(int i = 1, u, v; i <= M; i++){
        scanf("%d %d", &u, &v);
        G[u].push_back(i);
        G[v].push_back(-i);
        edges[i] = {u, v, 1, 1};
        redges[i] = {v, u, 0, -1};
    }

    int minCoins = minimum_cost_flow();
    if(minCoins == -1){
        printf("-1\n");
        return 0;
    }

    printf("%d\n", minCoins);
    for(int i = 0; i < K; i++){
        path.clear();
        dfs();

        int sz = (int) path.size();
        printf("%d\n", sz);
        for(int j = 0; j < sz; j++)
            printf("%d%c", path[j], (" \n")[j==sz-1]);
    }
}
/********************************************/

/*Graph algorithm*/
1. There are n cities and m roads between them. Your task is to process q
queries where you have to determine the length of the shortest route between two given cities.
int N, M, Q, a, b;
ll dist[maxN+1][maxN+1], c;

int main(){
    scanf("%d %d %d", &N, &M, &Q);
    memset(dist, 0x3f, sizeof(dist));
    for(int i = 0; i < M; i++){
        scanf("%d %d %lld", &a, &b, &c);
        dist[a][b] = min(dist[a][b], c);
        dist[b][a] = min(dist[b][a], c);
    }

    for(int i = 1; i <= N; i++) dist[i][i] = 0;
    for(int k = 1; k <= N; k++)
        for(int i = 1; i <= N; i++)
            for(int j = 1; j <= N; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    for(int q = 0; q < Q; q++){
        scanf("%d %d", &a, &b);
        printf("%lld\n", (dist[a][b] >= INF ? -1 : dist[a][b]));
    }
}
/*******************************/
2. You play a game consisting of n
 rooms and m tunnels. Your initial score is 0 , and each tunnel increases your score by x
 where x may be both positive or negative. You may go through a tunnel several times.
Your task is to walk from room 1 to room n . What is the maximum score you can get?

struct Edge {
    int a, b; ll c;
} edges[maxM];

int N, M;
ll dp[maxN];
bool vis[maxN], visR[maxN];
vector<int> G[maxN], GR[maxN];

void dfs(int u){
    vis[u] = true;
    for(int v : G[u])
        if(!vis[v])
            dfs(v);
}

void dfsR(int u){
    visR[u] = true;
    for(int v : GR[u])
        if(!visR[v])
            dfsR(v);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0, a, b; i < M; i++){
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        edges[i] = {a, b, -c};
        G[a].push_back(b);
        GR[b].push_back(a);
    }
    dfs(1); dfsR(N);

    fill(dp+2, dp+N+1, INF);
    bool improvement = true;
    for(int iter = 0; iter < N && improvement; iter++){
        improvement = false;
        for(int i = 0; i < M; i++){
            int u = edges[i].a;
            int v = edges[i].b;
            ll w = edges[i].c;

            if(dp[v] > dp[u]+w){
                dp[v] = dp[u]+w;
                improvement = true;

                if(iter == N-1 && vis[v] && visR[v]){
                    printf("-1\n");
                    return 0;
                }
            }
        }
    }

    printf("%lld\n", -dp[N]);
}
/****************************************/
3.Your task is to find a minimum-price flight route from Syrjälä to Metsälä. You have one discount coupon,
using which you can halve the price of any single flight during the route. However, you can only use the coupon once.

int dist1[N];
int dist2[N];
bool visited1[N], visited2[N];
vector<pair<int,int>> adj1[N],adj2[N];
void dik1(int s){
    priority_queue<pair<int,int>> q;
    dist1[s] = 0;
    q.push({0,s});
    while(!q.empty()){
        int a = q.top().second;
        q.pop();
        if(visited1[a]) continue;
        visited1[a] = true;
        for(auto u : adj1[a]){
            int b = u.first, w = u.second;
            if(dist1[a]+w<dist1[b]){
                dist1[b] = dist1[a]+w;
                q.push({-dist1[b],b});
            }
        }
    }
}
void dik2(int s){
    priority_queue<pair<int,int>> q;
    dist2[s] = 0;
    q.push({0,s});
    while(!q.empty()){
        int a = q.top().second;
        q.pop();
        if(visited2[a]) continue;
        visited2[a] = true;
        for(auto u : adj2[a]){
            int b = u.first, w = u.second;
            if(dist2[a]+w<dist2[b]){
                dist2[b] = dist2[a]+w;
                q.push({-dist2[b],b});
            }
        }
    }
}


void solution(){
    int n,m;
    cin >> n >> m;
    vector<array<int,3>>e;
    for(int i=0;i<m;i++){
        int x,y,w;
        cin >> x >> y >> w;
        e.push_back({x,y,w});
        adj1[x].push_back({y,w});
        adj2[y].push_back({x,w});
    }
    for(int i=0;i<=n;i++) dist1[i] = dist2[i] = inf;
    dist1[1] = 0;
    dist2[n] = 0;
    dik1(1);
    dik2(n);
    int res = inf;
    for(auto [x,y,w] : e){
        res = min(res, dist1[x] + (w/2) + dist2[y]);
    }
    cout << res << '\n';
}
/*************************************/

4.Byteland has n cities and m flight connections.
Your task is to design a round trip that begins in a city, goes through one or more other cities, and finally returns to the starting city.
Every intermediate city on the route has to be distinct.

int N, M, start, finish, p[maxN], vis[maxN];
vector<int> ans, G[maxN];

void dfs(int u){
    vis[u] = 1;
    for(int v : G[u]){
        if(vis[v] == 0){
            p[v] = u;
            dfs(v);
            if(start)
                return;
        } else if(vis[v] == 1){
            finish = u;
            start = v;
            return;
        }
    }
    vis[u] = 2;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0, a, b; i < M; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
    }

    for(int i = 1; i <= N && !start; i++)
        if(vis[i] == 0)
            dfs(i);

    if(!start){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    ans.push_back(start);
    for(int u = finish; u != start; u = p[u])
        ans.push_back(u);
    ans.push_back(start);
    reverse(ans.begin(), ans.end());

    int K = (int) ans.size();
    printf("%d\n", K);
    for(int i = 0; i < K; i++)
        printf("%d%c", ans[i], (" \n")[i==K-1]);
}

/******************************/
5. Uolevi has won a contest, and the prize is a free flight trip that can consist of one or more flights through cities.
Of course, Uolevi wants to choose a trip that has as many cities as possible.
Uolevi wants to fly from Syrjälä to Lehmälä so that he visits the maximum number of cities.
You are given the list of possible flights, and you know that there are no directed cycles in the flight network.

bool vis[maxN];
int N, M, K, a, b, in[maxN], p[maxN], l[maxN], ans[maxN];
vector<int> G[maxN];
queue<int> Q;

void dfs(int u, int par = 0){
    vis[u] = true;
    for(int v : G[u])
        if(v != par && !vis[v])
            dfs(v, u);
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        in[b]++;
    }

    dfs(1);
    if(!vis[N]){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    fill(l+2, l+maxN, -1);
    for(int i = 1; i <= N; i++)
        if(in[i] == 0)
            Q.push(i);

    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int v : G[u]){
            if(l[u] != -1 && l[v] < l[u]+1){
                l[v] = l[u] + 1;
                p[v] = u;
            }
            in[v]--;
            if(in[v] == 0)
                Q.push(v);
        }
    }

    K = l[N] - l[1];
    printf("%d\n", K+1);
    for(int i = K, u = N; i >= 0; i--){
        ans[i] = u;
        u = p[u];
    }
    for(int i = 0; i <= K; i++)
        printf("%d%c", ans[i], (" \n")[i==K]);
}

/****************************/
6. You are going to travel from Syrjälä to Lehmälä by plane. You would like to find answers to the following questions:
-what is the minimum price of such a route?
-how many minimum-price routes are there? (modulo 109+7)
-what is the minimum number of flights in a minimum-price route?
-what is the maximum number of flights in a minimum-price route?

typedef pair<int,ll> edge;
typedef pair<ll,int> node;
const int maxN = 1e5+1;
const ll MOD = 1e9+7;
const ll INF = 0x3f3f3f3f3f3f;

int N, M, a, b, minR[maxN], maxR[maxN];
ll c, dist[maxN], ways[maxN];
vector<edge> G[maxN];

struct Comparator {
    bool operator() (int x, int y) const {
        return dist[x] == dist[y] ? x < y : dist[x] < dist[y];
    }
};
set<int, Comparator> PQ;

int main(){
    scanf("%d %d", &N, &M);
    memset(dist, 0x3f, sizeof(dist));
    for(int i = 0; i < M; i++){
        scanf("%d %d %lld", &a, &b, &c);
        G[a].push_back({b, c});
    }

    PQ.insert(1);
    ways[1] = 1;
    dist[1] = 0;
    while(!PQ.empty()){
        int u = *PQ.begin();
        ll d = dist[u];
        PQ.erase(PQ.begin());

        for(edge e : G[u]){
            int v = e.first;
            ll w = e.second;
            if(d + w <= dist[v]){
                if(dist[v] != INF)  PQ.erase(v);
                if(d + w == dist[v]){
                    ways[v] = (ways[u] + ways[v]) % MOD;
                    minR[v] = min(minR[v], minR[u]+1);
                    maxR[v] = max(maxR[v], maxR[u]+1);
                }
                if(d + w < dist[v]){
                    dist[v] = d+w;
                    ways[v] = ways[u];
                    minR[v] = minR[u]+1;
                    maxR[v] = maxR[u]+1;
                }
                PQ.insert(v);
            }
        }
    }

    printf("%lld %lld %d %d\n", dist[N], ways[N], minR[N], maxR[N]);
}
/****************************************/
7. There are n cities and m flight connections between them.
You want to travel from Syrjälä to Lehmälä so that you visit each city exactly once. How many possible routes are there?

int N, M;
bool inqueue[maxN][SIZE];
ll dp[maxN][SIZE];
vector<int> G[maxN];
queue<pii> Q;

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0, a, b; i < M; i++){
        scanf("%d %d", &a, &b);
        G[a-1].push_back(b-1);
    }

    dp[0][1] = 1;
    Q.push({0, 1});
    inqueue[0][1] = true;
    while(!Q.empty()){
        int u = Q.front().first;
        int mask = Q.front().second;
        Q.pop();

        if(u != N-1){
            for(int v : G[u]){
                int newMask = mask|(1<<v);
                if((mask&(1<<v)) == 0){
                    dp[v][newMask] += dp[u][mask];
                    dp[v][newMask] %= MOD;
                    if(!inqueue[v][newMask]){
                        Q.push({v, newMask});
                        inqueue[v][newMask] = true;
                    }
                }
            }
        }
    }

    printf("%lld\n", dp[N-1][(1<<N)-1]);
}
/********************************/
8. Consider a network consisting of n computers and m
connections. Each connection specifies how fast a computer can send data to another computer.
Kotivalo wants to download some data from a server. What is the maximum speed he can do this, using the connections in the network?

typedef pair<int,ll> pil;
const int maxN = 501;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int N, M, p[maxN];
ll cap[maxN][maxN];
vector<int> G[maxN];

ll bfs(int s = 1, int t = N){
    fill(p+1, p+N+1, -1);
    p[s] = -2;

    queue<pil> Q;
    Q.push({s, INF});
    while(!Q.empty()){
        int u = Q.front().first;
        ll f = Q.front().second;
        Q.pop();

        for(int v : G[u]){
            if(p[v] == -1 && cap[u][v]){
                p[v] = u;
                ll aug = min(f, cap[u][v]);
                if(v == t)  return aug;
                Q.push({v, aug});
            }
        }
    }

    return 0;
}

ll maxflow(int s = 1, int t = N){
    ll flow = 0, aug = 0;
    while(aug = bfs()){
        flow += aug;
        int u = t;
        while(u != s){
            int v = p[u];
            cap[v][u] -= aug;
            cap[u][v] += aug;
            u = v;
        }
    }
    return flow;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0, a, b; i < M; i++){
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        G[a].push_back(b);
        G[b].push_back(a);
        cap[a][b] += c;
    }
    printf("%lld\n", maxflow());
}
/************************************/
9. A game consists of n rooms and m
 teleporters. At the beginning of each day, you start in room 1 and you have to reach room n.
You can use each teleporter at most once during the game. How many days can you play if you choose your routes optimally?

typedef pair<int,int> pii;
const int maxN = 501, maxM = 1001;
const int INF = 0x3f3f3f3f;

int N, M, p[maxN], cap[maxN][maxN];
bool vis[maxM];
vector<int> path, F[maxN];
vector<pii> G[maxN];

int bfs(int s = 1, int t = N){
    fill(p+1, p+N+1, -1);
    p[s] = -2;

    queue<pii> Q;
    Q.push({s, INF});
    while(!Q.empty()){
        int u = Q.front().first;
        int f = Q.front().second;
        Q.pop();

        for(int v : F[u]){
            if(p[v] == -1 && cap[u][v]){
                p[v] = u;
                int aug = min(f, cap[u][v]);
                if(v == t)  return aug;
                Q.push({v, aug});
            }
        }
    }

    return 0;
}

void dfs(int u = 1){
    path.push_back(u);
    if(u == N)  return;
    for(pii e : G[u]){
        int v = e.first;
        int id = e.second;
        if(cap[u][v] == 0 && !vis[id]){
            vis[id] = true;
            dfs(v);
            return;
        }
    }
}

int maxflow(int s = 1, int t = N){
    int flow = 0, aug = 0;
    while(aug = bfs()){
        flow += aug;
        int u = t;
        while(u != s){
            int v = p[u];
            cap[v][u] -= aug;
            cap[u][v] += aug;
            u = v;
        }
    }
    return flow;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0, a, b; i < M; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back({b, i});
        F[a].push_back(b);
        F[b].push_back(a);
        cap[a][b]++;
    }

    int K = maxflow();
    printf("%d\n", K);
    for(int k = 0; k < K; k++){
        path.clear();

        dfs();
        int sz = (int) path.size();
        printf("%d\n", sz);
        for(int i = 0; i < sz; i++)
            printf("%d%c", path[i], (" \n")[i==sz-1]);
    }
}
/*****************************************/
10. Kaaleppi has just robbed a bank and is now heading to the harbor.
However, the police wants to stop him by closing some streets of the city.
What is the minimum number of streets that should be closed so that there is no route between the bank and the harbor?

typedef pair<int,int> pii;
const int maxN = 501;
const int INF = 0x3f3f3f3f;

int N, M, p[maxN], cap[maxN][maxN];
bool vis[maxN];
vector<int> G[maxN];

int bfs(int s = 1, int t = N){
    fill(p+1, p+N+1, -1);
    p[s] = -2;

    queue<pii> Q;
    Q.push({s, INF});
    while(!Q.empty()){
        int u = Q.front().first;
        int f = Q.front().second;
        Q.pop();

        for(int v : G[u]){
            if(p[v] == -1 && cap[u][v]){
                p[v] = u;
                int aug = min(f, cap[u][v]);
                if(v == t)  return aug;
                Q.push({v, aug});
            }
        }
    }

    return 0;
}

void dfs(int u = 1){
    vis[u] = true;
    for(int v : G[u])
        if(!vis[v] && cap[u][v])
            dfs(v);
}

int maxflow(int s = 1, int t = N){
    int flow = 0, aug = 0;
    while(aug = bfs()){
        flow += aug;
        int u = t;
        while(u != s){
            int v = p[u];
            cap[v][u] -= aug;
            cap[u][v] += aug;
            u = v;
        }
    }
    return flow;
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0, a, b; i < M; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
        cap[a][b]++;
        cap[b][a]++;
    }
    printf("%d\n", maxflow());

    dfs();
    for(int u = 1; u <= N; u++){
        if(!vis[u]) continue;
        for(int v : G[u])
            if(!vis[v])
                printf("%d %d\n", u, v);
    }
}

/******************************************/
/*Trees*/
1. You are given a tree consisting of n nodes.
Your task is to determine for each node the maximum distance to another node.

vector<int>adj[N];
int dist[2][N];

int dfs(int u,int par,int depth,int i)
{
    dist[i][u] = depth;
    int start = -1;
    for(auto x : adj[u]){
        if(x == par) continue;
        int p = dfs(x,u,depth+1,i);
        if(start == -1 || dist[i][p] > dist[i][start]) start = p;
    }

    return start == -1 ? u : start;
}

void solution(){
    int n;
    cin >> n;
    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
        --x,--y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int first_max = dfs(0,0,0,0);
    int second_max = dfs(first_max,first_max,0,0);

    dfs(second_max,second_max,0,1);

    for(int i=0;i<n;i++){
        cout << max(dist[0][i],dist[1][i]) << ' ';
    }
    cout << '\n';
}
/********************************/
2. You are given a tree consisting of n nodes.
Your task is to determine for each node the sum of the distances from the node to all other nodes.

vector<int>e[N];
int sum[N];
int dp[N];
int n;
void dfs(int u,int p,int depth){
    sum[1]+=depth;
    dp[u] = 1;
    for(auto x : e[u]){
        if(x == p) continue;
       // sum[x]+=sum[u];
        dfs(x,u,depth + 1);
        dp[u]+=dp[x];
    }

}

void dfs2(int u,int p){
    for(auto x : e[u]){
        if(x == p) continue;
        sum[x] = sum[u] + n - 2*dp[x];
        dfs2(x , u);
    }

}

void solution(){
   // int n;
    cin >> n;
    for(int i=0;i<n-1;i++){
        int x,y;
        cin >> x >> y;
       // --x, --y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(1,0,0);
    dfs2(1,0);
    for(int i=1;i<=n;i++){
        cout << sum[i] << ' ';
    }
}
/******************************************/
3. You are given a tree consisting of n nodes, and m paths in the tree.
Your task is to calculate for each node the number of paths containing that node.

int N, M, a, b, sub[maxN], p[maxN][logN];
int timer, in[maxN], out[maxN];
vector<int> G[maxN];

void dfs1(int u = 1, int par = 1){
    in[u] = ++timer;
    p[u][0] = par;
    for(int i = 1; i < logN; i++)
        p[u][i] = p[p[u][i-1]][i-1];
    for(int v : G[u])
        if(v != par)
            dfs1(v, u);
    out[u] = ++timer;
}

void dfs2(int u = 1){
    for(int v : G[u]){
        if(v != p[u][0]){
            dfs2(v);
            sub[u] += sub[v];
        }
    }
}

bool ancestor(int u, int v){
    return in[u] <= in[v] && out[u] >= out[v];
}

int lca(int u, int v){
    if(ancestor(u, v))  return u;
    if(ancestor(v, u))  return v;
    for(int i = logN-1; i >= 0; i--)
        if(!ancestor(p[u][i], v))
            u = p[u][i];
    return p[u][0];
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N-1; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs1();

    for(int i = 0; i < M; i++){
        scanf("%d %d", &a, &b);
        int l = lca(a, b);
        sub[a]++; sub[b]++;
        sub[l]--;
        if(l != 1)
            sub[p[l][0]]--;
    }

    dfs2();

    for(int i = 1; i <= N; i++)
        printf("%d%c", sub[i], (" \n")[i==N]);
}
/*************************************/
4. You are given a rooted tree consisting of n
 nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a value.

Your task is to process following types of queries:
-change the value of node s to x.
-calculate the sum of values in the subtree of node s

int n,q;
int fenw[N];
vector<int>e[N];

void modify(int x, int v) {
    while (x <= n) {
        fenw[x] += v;
        x += (x & -x);
    }
}
int get(int x) {
    int v = 0;
    while (x > 0) {
        v += fenw[x];
        x -= (x & -x);
    }
    return v;
}
int get(int l,int r){ return get(r)-get(l-1); }

int start[N],en[N];
int timer;
int value[N];

void dfs(int u,int par){
    start[u] = ++timer;
    modify(timer, value[u]);
    for(auto x : e[u]){
        if(x==par) continue;
        dfs(x,u);
    }
    en[u] = timer;
}


void solution(){
    cin >> n >> q;
    for(int i=1;i<=n;i++) cin >> value[i];

    for(int i=1;i<n;i++){
        int x,y;
        cin >> x >> y;
        e[x].push_back(y);
        e[y].push_back(x);
    }
    dfs(1,0);
    while(q--){
        int t; cin >> t;
        if(t == 1){
            int s,x;
            cin >> s >> x;
            modify(start[s],-value[s]);
            value[s] = x;
            modify(start[s],value[s]);
        }
        else{
            int s;
            cin >> s;
            cout << get(start[s],en[s]) << '\n';
        }
    }
}
/************************************/
5. You are given a rooted tree consisting of n
 nodes. The nodes are numbered 1,2,…,n, and node 1 is the root. Each node has a value.

Your task is to process following types of queries:
-change the value of node s to x.
-calculate the sum of values on the path from the root to node s

int N, Q, a, b, t, s;
int timer, in[maxN], out[maxN];
ll x, v[maxN], ds[2*maxN];
vector<int> G[maxN];

void update(int idx, ll val){
    for(int i = idx; i <= timer; i += -i&i)
        ds[i] += val;
}

ll query(int idx){
    ll sum = 0;
    for(int i = idx; i > 0; i -= -i&i)
        sum += ds[i];
    return sum;
}

void dfs(int u = 1, int p = 0){
    in[u] = ++timer;
    for(int c : G[u])
        if(c != p)
            dfs(c, u);
    out[u] = ++timer;
}

int main(){
    scanf("%d %d", &N, &Q);
    for(int i = 1; i <= N; i++)
        scanf("%lld", &v[i]);
    for(int i = 0; i < N-1; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs();
    for(int i = 1; i <= N; i++){
        update(in[i], v[i]);
        update(out[i], -v[i]);
    }

    for(int q = 0; q < Q; q++){
        scanf("%d %d", &t, &s);
        if(t == 1){
            scanf("%lld", &x);
            update(in[s], -v[s]);
            update(out[s], v[s]);
            update(in[s], x);
            update(out[s], -x);
            v[s] = x;
        } else if(t == 2){
            printf("%lld\n", query(in[s]));
        }
    }
}
/***************************************/

6.You are given a tree consisting of n
 nodes. The nodes are numbered 1,2,…,n. Each node has a value.

Your task is to process following types of queries:
-change the value of node s to x
-find the maximum value on the path between nodes a and b.

using namespace std;
const int maxN = 2e5+1;

int N, Q, k, x, y, root, idcounter;

struct Lazy {
    int a = 1, b = 0;
    bool empty(){
        return (a == 1 && b == 0);
    }
};

struct Node {
    Lazy tag;
    bool rev = false;
    Node *c[2] = {nullptr, nullptr}, *p = nullptr;
    int sz, val, sum, mn, mx, id = ++idcounter;

    Node(int v){
        sz = 1;
        val = sum = mn = mx = v;
    }

    void apply(Lazy other){
        mn = mn*other.a + other.b;
        mx = mx*other.a + other.b;
        val = val*other.a + other.b;
        sum = sum*other.a + sz*other.b;
        tag = {tag.a*other.a, tag.b*other.a+other.b};
    }

    void push(){
        if(rev){
            swap(c[0], c[1]);
            if(c[0])    c[0]->rev ^= true;
            if(c[1])    c[1]->rev ^= true;
            rev = false;
        }
        if(!tag.empty()){
            if(c[0])    c[0]->apply(tag);
            if(c[1])    c[1]->apply(tag);
            tag = Lazy();
        }
    }

    void pull(){
        sum = mn = mx = val;
        sz = 1;
        for(int i = 0; i < 2; i++){
            if(c[i]){
                mn = min(mn, c[i]->mn);
                mx = max(mx, c[i]->mx);
                sum += c[i]->sum;
                sz += c[i]->sz;
            }
        }
    }
} *LCT[maxN];

bool notRoot(Node *t){
    return t->p && (t->p->c[0] == t || t->p->c[1] == t);
}

void rotate(Node *t){
    Node *p = t->p;
    bool b = (p->c[0] == t);
    if((t->p = p->p) && notRoot(p)) t->p->c[(t->p->c[1] == p)] = t;
    if((p->c[!b]=t->c[b]))          p->c[!b]->p = p;
    t->c[b] = p;
    p->p = t;
    p->pull();
}


void splay(Node *t){
    while(notRoot(t)){
        Node *p = t->p;
        p->push();
        t->push();
        rotate(t);
    }
    t->push();
    t->pull();
}

Node* access(Node *t){
    Node *last = nullptr;
    for(Node *u = t; u; u = u->p){
        splay(u);
        u->c[1] = last;
        last = u;
    }
    splay(t);
    return last;
}

void evert(Node *t){
    access(t);
    t->rev = true;
}

void link(Node *u, Node *v){
    evert(u);
    u->p = v;
}

void cut(Node *u, Node *v){
    evert(u);
    access(v);
    if(v->c[0]) v->c[0]->p = 0;
    v->c[0] = 0;
    v->pull();
}

Node* path(Node *u, Node *v){
    evert(u);
    access(v);
    return v;
}

Node* LCA(Node *u, Node *v){
    evert(LCT[root]);
    access(u);
    return access(v);
}

bool connected(Node *u, Node *v){
    path(u, v);
    while(v->c[0])
        v = v->c[0];
    return u == v;
}

int main(){
    scanf("%d %d", &N, &Q);
    for(int i = 1; i <= N; i++){
        scanf("%d", &x);
        LCT[i] = new Node(x);
    }
    for(int i = 0; i < N-1; i++){
        scanf("%d %d", &x, &y);
        link(LCT[x], LCT[y]);
    }

    root = 1;
    for(int i = 0; i < Q; i++){
        scanf("%d", &k);
        if(k == 1){
            scanf("%d %d", &x, &y);
            Node *p = path(LCT[x], LCT[x]);
            p->apply({0, y});
        } else if(k == 2){
            scanf("%d %d", &x, &y);
            Node *p = path(LCT[x], LCT[y]);
            printf("%d ", p->mx);
        }
    }
}
/****************************/
7. You are given a rooted tree consisting of n
nodes. The nodes are numbered 1,2...,n, and node 1 is the root. Each node has a color.
Your task is to determine for each node the number of distinct colors in the subtree of the node.

int N, a, b, c[maxN], x[2*maxN], ptr[2*maxN], ds[2*maxN], ans[maxN];
int timer, in[maxN], out[maxN];
triple queries[maxN];
vector<int> G[maxN];
map<int,int> mp;
set<int> S;

void dfs(int u = 1, int p = 0){
    in[u] = ++ timer;
    for(int v : G[u])
        if(v != p)
            dfs(v, u);
    out[u] = ++timer;
}

void update(int idx, int val){
    for(int i = idx; i <= 2*N; i += -i&i)
        ds[i] += val;
}

int query(int idx){
    int sum = 0;
    for(int i = idx; i > 0; i -= -i&i)
        sum += ds[i];
    return sum;
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i <= N; i++)
        scanf("%d", &c[i]);

    for(int i = 0; i < N-1; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs();

    for(int i = 1; i <= N; i++)
        x[in[i]] = x[out[i]] = c[i];

    for(int i = 2*N; i > 0; i--){
        if(mp[x[i]])
            ptr[i] = mp[x[i]];
        mp[x[i]] = i;
    }

    for(int i = 1; i <= 2*N; i++){
        if(S.count(x[i]) == 0)
            update(i, 1);
        S.insert(x[i]);
    }

    for(int i = 1; i <= N; i++)
        queries[i-1] = {in[i], out[i], i-1};
    sort(queries, queries+N);

    int l = 1;
    for(int i = 0; i < N; i++){
        while(l < queries[i][0]){
            if(ptr[l])
                update(ptr[l], 1);
            l++;
        }
        ans[queries[i][2]] = query(queries[i][1]) - query(queries[i][0]-1);
    }

    for(int i = 0; i < N; i++)
        printf("%d%c", ans[i], (" \n")[i==N-1]);
}
/********************************/
8. Given a tree of n nodes, your task is to find a centroid, i.e.,
 a node such that when it is appointed the root of the tree, each subtree has at most ceil(n/2) nodes.

 int N, a, b, p[maxN], sz[maxN];
vector<int> G[maxN];

void dfs(int u = 1){
    sz[u] = 1;
    for(int v : G[u]){
        if(v != p[u]){
            p[v] = u;
            dfs(v);
            sz[u] += sz[v];
        }
    }
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N-1; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs();

    for(int i = 1; i <= N; i++){
        bool centroid = true;

        if(p[i] != 0 && N-sz[i] > N/2)
            centroid = false;

        for(int v : G[i])
            if(v != p[i] && sz[v] > N/2)
                centroid = false;

        if(centroid){
            printf("%d\n", i);
            return 0;
        }
    }
}
/****************************/
9. Given a tree of n nodes, your task is to count the number of distinct paths that have at least k1
and at most k2 edges.

int N, A, B, deepest, sz[maxN];
bool vis[maxN];
ll ans, ds[maxN];
vector<int> G[maxN];

void update(int idx, ll val){
    for(int i = idx+1; i <= N; i += -i&i) ds[i] += val;
}

ll query(int idx){
    ll res = 0;
    for(int i = idx+1; i > 0; i -= -i&i)
        res += ds[i];
    return res;
}

int getSize(int u = 1, int p = -1){
    sz[u] = 1;
    for(int v : G[u])
        if(v != p && !vis[v])
            sz[u] += getSize(v, u);

    return sz[u];
}

int centroid(int u, int p, int n){
    for(int v : G[u])
        if(v != p && !vis[v] && sz[v] > n/2)
            return centroid(v, u, n);

    return u;
}

void dfs(int u, int p, bool t, int d = 1){
    if(d > B)   return;

    deepest = max(deepest, d);
    if(t)   update(d, 1);
    else {
        ans += query(B-d);
        ans -= query(max(0, A-d)-1);
    }

    for(int v : G[u])
        if(v != p && !vis[v])
            dfs(v, u, t, d+1);
}

void solve(int u = 1){
    int c = centroid(u, -1, getSize(u));
    vis[c] = true;
    deepest = 0;

    for(int v : G[c]){
        if(!vis[v]){
            dfs(v, c, false);
            dfs(v, c, true);
        }
    }
    for(int i = 1; i <= deepest; i++)
        update(i, -query(i)+query(i-1));

    for(int v : G[c])
        if(!vis[v])
            solve(v);
}
int main(){
    scanf("%d %d %d", &N, &A, &B);
    for(int i = 0, a, b; i < N-1; i++){
        scanf("%d %d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    update(0, 1);
    solve();
    printf("%lld\n", ans);
}
/***********************************/
