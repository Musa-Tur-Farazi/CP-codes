#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define I_love_you_Liny ios_base::sync_with_stdio(false); cin.tie(nullptr)
#define int long long int
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(),(x).rend()

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
const int N = 301000;
const int mod = 1000000007;

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


void solution(){
    string s = "babbabbabc";
    manacher m;
    m.build(s);

}

bool multi_test = 0;

int32_t main(){

    I_love_you_Liny;
    int T = 1;
    if(multi_test) cin >> T;
    while(T--) solution();

    return 0;

}

