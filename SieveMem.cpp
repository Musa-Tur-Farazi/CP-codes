const int mx = 1e7+9;
const int mxp = 1e7 + 9;
int sz = 0;
bitset<mx>mark;
int primes[mxp];
int lp[mxp];

void sieve(){
    mark[0] = mark[1] = 1;
    primes[sz++] = 2;
    int lim = sqrt(mx*1.0) + 2, till = 0;
    for(int i=4;i<mx;i+=2) mark[i] = 1;
    for(int i=3;i<mx;i+=2){
        if(!mark[i]){
            primes[sz++] = i;
            if(i <= lim){ for(int j=i*i;j<mx;j+=i) mark[j] = 1; }
        }
    }
    for(int i=2;i<mx;i++){
        if(lp[i]==0){ lp[i] = i; till++; }
        for(int j=0;j<till && primes[j]<=lp[i] && i*primes[j]<=mx;j++) lp[i*primes[j]]=primes[j];
    }
}
