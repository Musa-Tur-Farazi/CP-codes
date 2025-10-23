#include <bits/stdc++.h>
using namespace std;
#define I_love_you_Liny cin.tie(0)->sync_with_stdio(0)
//#define int long long int
#define all(x)     (x).begin(), (x).end()
#define rall(x)    (x).rbegin(),(x).rend()
const long long inf = 3e18;
const int mod = 1e9+7;
const int N = 3e5+5;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

// AtCoder
const i64 CYCLES_PER_SEC = 3000000000;

struct Timer {
	i64 start;
	Timer(){reset();}
	void reset(){start=getCycle();}
	inline double get(){return (double)(getCycle()-start)/CYCLES_PER_SEC;}
	inline i64 getCycle(){
		u32 low,high;
		__asm__ volatile ("rdtsc" : "=a" (low), "=d" (high));
		return ((i64)low)|((i64)high<<32);
	}
};

Timer timer;

uint32_t xor128(){
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t = x ^ (x << 11);
  x = y; y = z; z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

int c[27];
int s[367][27];
int ls[27];
int d;
int r[27][367];
using BS = bitset<64*6>;
BS v[27];
int score(vector<int>&t){
    for(int i=1; i<=26; i++) ls[i] = 0;
    int tot = 0;
    for(int i=1; i<=d; i++){
        int neg = 0;
        ls[t[i]]=i;
        for(int j=1; j<=26; j++) neg+=c[j]*(i-ls[j]);
        tot+=s[i][t[i]]-neg;
      //  cout << "Score at step : " << i << ' ' << tot << '\n';
    }
    return tot;
}
int caldif(int p){
    int res = 0;
    int cp=c[p], lp=0;
    for(int i=v[p]._Find_first(); i<(int)v[p].size(); i=v[p]._Find_next(i)){
        res-=c[p]*(i-lp)*(i-lp-1)/2;
        res+=r[p][i];
        lp=i;
    }
    return res;
}
void solve(){
    cin >> d;
    for(int i=1; i<=26; i++) cin >> c[i];
    for(int i=1; i<=d; i++){
        for(int j=1; j<=26; j++){
            cin >> s[i][j];
            r[j][i]=s[i][j];
        }
    }
    //greedy
    vector<int>t(d+5);
    memset(ls,0,sizeof ls);
    for(int i=1; i<=d; i++){
        vector<int>ss(28,0);
        for(int j=1; j<=26; j++){
            ss[j]=s[i][j]+c[j]*(i-ls[j]);
        }
        t[i]=max_element(all(ss))-ss.begin();
        ls[t[i]]=i;
        v[t[i]].set(i);
    }
    for(int j=1; j<=26; j++) v[j].set(d+1);
    int tmpscore = score(t);
    int itr = 0;
    const double LIM = 1.8;
    double stemp = 2000, etemp=200;
    while(timer.get()<LIM){
        itr++;
        if(itr%2==0){
            int dd=xor128()%d+1;
            int qq=xor128()%26+1;
            int p = t[dd];
            if(p==qq) qq=(qq+1)%26+1;
            int nxtscore=tmpscore;
            nxtscore-=caldif(p)+caldif(qq);
            v[t[dd]].flip(dd);
            t[dd]=qq;
            v[t[dd]].flip(dd);
            nxtscore+=caldif(p)+caldif(qq);
            double temp = stemp+(etemp-stemp)*timer.get()/LIM;
            double prob = std::exp((nxtscore-tmpscore)/temp);
            const int INF = 1<<30;
            if(prob > (xor128()%INF)/(double)(INF)){
                tmpscore=nxtscore;
            }
            else{
                v[t[dd]].flip(dd);
                t[dd]=p;
                v[t[dd]].flip(dd);
            }
        }
        else{
            int x=xor128()%d+1;
            int y=xor128()%d+1;
            int p=t[x];
            int q=t[y];
            if(p==q) continue;
            int nxtscore=tmpscore;
            nxtscore-=caldif(p)+caldif(q);
            v[t[x]].flip(x);
            v[t[y]].flip(y);
            swap(t[x],t[y]);
            v[t[x]].flip(x);
            v[t[y]].flip(y);
            nxtscore+=caldif(p)+caldif(q);
            double temp=stemp+(etemp-stemp)*timer.get()/LIM;
            double prob=std::exp((nxtscore-tmpscore)/temp);
            const int INF=1<<30;
            if(prob>(xor128()%INF)/(double)INF){
                tmpscore=nxtscore;
            }
            else{
                v[t[x]].flip(x);
                v[t[y]].flip(y);
                swap(t[x],t[y]);
                v[t[x]].flip(x);
                v[t[y]].flip(y);
            }
        }
    }
    cerr << itr << endl;
    cerr << tmpscore << ":" << score(t) << endl;
    for(int i=1; i<=d; i++) cout << t[i] << '\n';
}
int32_t main(){
    I_love_you_Liny;
    int T = 1;
    while(T--) solve();
    return 0;
}
