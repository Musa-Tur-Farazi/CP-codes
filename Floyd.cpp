#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define I_love_you_Liny ios_base::sync_with_stdio(false); cin.tie(nullptr)
#define sync_clock chrono::steady_clock::now().time_since_epoch().count()
#define int long long int
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(),(x).rend()

template<typename T> struct split64_hash { inline static uint64_t splitmix64(uint64_t x){
    x = ((x += 0x9e3779b97f4a7c15) ^ ((x += 0x9e3779b97f4a7c15) >> 30)) * 0xbf58476d1ce4e5b9;
    return ((x ^ (x >> 27)) * 0x94d049bb133111eb) ^ (((x ^ (x >> 27)) * 0x94d049bb133111eb) >> 31);
   } inline size_t operator()(uint64_t x) const{static const uint64_t FIX = sync_clock; return splitmix64(x + FIX);}
};
template <typename T,typename V,typename U = int> using u_map = unordered_map<T, V, split64_hash <U>>;
template <typename T> using orset =  tree<T, null_type, less<T>,  rb_tree_tag,   tree_order_statistics_node_update>;
template <typename T, typename V> using ormap = tree<T, V, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> istream& operator>>(istream& is,  vector<T> &a){for (auto &x : a) is >> x;         return is;}
template <typename T> ostream& operator<<(ostream& os,  vector<T>  a){for (auto &x : a) os << x << ' ';  return os;}
template <typename T> ostream& operator<<(ostream& os,  set<T>  s){for (auto &x : s) os << x << ' ';     return os;}
template <typename T> ostream& operator<<(ostream& os,  multiset<T>  s){for (auto &x : s) os << x << ' ';return os;}
template <typename T, typename V> void operator+=(vector<T>& a, const V value) { for(auto &x : a)x += value; }
template <typename T, typename V> void operator-=(vector<T>& a, const V value) { for(auto &x : a)x -= value; }
template <typename T, typename V> void operator*=(vector<T>& a, const V value) { for(auto &x : a)x *= value; }
template <typename T, typename V> void operator/=(vector<T>& a, const V value) { for(auto &x : a)x /= value; }
template <typename T> void operator++(vector<T>& a) { a += 1; }
template <typename T> void operator--(vector<T>& a) { a -= 1; }

const long long inf = 0x3f3f3f3f3f3f3f3f;
const int N = 2505;
const int mod = 1000000007;

int dis[N][N];

void solution(){
    int n,m;
    cin >> n >> m;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++) dis[i][j] = -inf;
        dis[i][i] = 0;
    }
    for(int i=0;i<m;i++){
        int x,y,w;
        cin >> x >> y >> w;
        dis[x][y] = min(dis[x][y],w);
        dis[y][x] = min(dis[y][x],w);

    }
    for(int k =1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }



}

bool multi_test = 0;

int32_t main(){

    I_love_you_Liny;
    int T = 1;
    if(multi_test) cin >> T;
    while(T--) solution();

    return 0;

}

