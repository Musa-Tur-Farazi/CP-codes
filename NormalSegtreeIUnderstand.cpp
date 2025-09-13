#include <bits/stdc++.h>
using namespace std;

#define int long long
const int inf = 3e18;
const int N = 2e5+5;

int a[22][N];
int f[1<<21],cst[1<<21];
int n;
void fwht(bool inv){
    int sz = (1<<n);
    for(int len = 1; len < sz; len <<= 1){
        for(int i = 0; i < sz; i += len<<1){
            for(int j = 0; j < len; j++){
                int u = f[i + j];
                int v = f[i + j + len];
                int u1 = cst[i + j];
                int v1 = cst[i + j + len];
                f[i + j]     = u + v;
                f[i + j + len] = u - v;
                cst[i + j] = u1 + v1;
                cst[i + j + len] = u1 - v1;
            }
        }
    }
    if(inv){
        for(int i=0; i<sz; i++){
            f[i]/=sz;
            cst[i]/=sz;
        }
    }
}

void solve(){
    int m; cin >> n >> m;
    for(int i=0; i<n; i++){
        string s; cin >> s;
        for(int j=0; j<m; j++) a[i][j] = (s[j]-'0');
    }
    for(int j=0; j<m; j++){
        int msk = 0;
        for(int i=0; i<n; i++){
            if(a[i][j]==1){
                msk|=(1<<i);
            }
        }
        f[msk]++;
    }
    for(int msk=0; msk<(1<<n); msk++){
        int pc = __builtin_popcount(msk);
        cst[msk] = min(pc,n-pc);
    }
    fwht(0);
    for(int i=0; i<(1<<n); i++) f[i]*=cst[i];

    fwht(1);
    int res = inf;
    for(int i=0; i<(1<<n); i++) res = min(res,f[i]);
    cout << res << '\n';

}

int32_t main(){
    cin.tie(0)->sync_with_stdio(0);
    int T = 1;
    while(T--) solve();
    return 0;
}
