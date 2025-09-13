//prefix
template<typename T = int, int B = 64>
struct Basis {
    T a[B];
    int sz;
    Basis() {
        for(int i=0;i<B;i++) a[i] = 0;
        sz = 0;
    }
    void insert(T x){
        for(int i=B-1;i>=0;i--){
            if((x&1LL<<i)==0) continue;
            if(!a[i]){
                a[i] = x;
                sz++;
                return;
            }
            x^=a[i];
        }
    }
    bool can(T x) {
        for(int i=B;i>=0;i--){
            if(x>>i&1LL) x^=a[i];
        }
        return x==0;
    }
    T max_xor(T ans = 0) {
        for(int i = B - 1; i >= 0; i--) {
            ans = max(ans, ans ^ a[i]);
        }
        return ans;
    }
};

//For arbitrary range

template<typename T = int, int N = 200005, int B = 30>
struct Basis {
    T a[N][B];
    T lst[N][B];
    int sz;
    Basis() {
        memset(a, 0, sizeof a);
        memset(lst, 0, sizeof lst);
        sz = 0;
    }
    void insert(T x,int pos){
        for(int i=0;i<B;i++) a[pos][i]=a[pos-1][i], lst[pos][i]=lst[pos-1][i];
        int cur = pos;
        for(int i=B;i>=0;i--){
            if((x&1LL<<i)==0) continue;
            if(!a[i]){
                a[pos][i] = x;
                lst[pos][i] = cur;
                sz++;
                return;
            }
            if(lst[pos][i]<cur){
                swap(lst[pos][i],cur);
                swap(x,a[pos][i]);
            }
            x^=a[i];
        }
    }
    bool can(int l,int r,T x) {
        for(int i=B;i>=0;i--){
            if(x>>i&1LL){
                if(lst[r][i]>=l) x^=a[r][i];
            }
        }
        return x==0;
    }
//    T max_xor(T ans = 0) {
//        for(int i = B - 1; i >= 0; i--) {
//            ans = max(ans, ans ^ a[i]);
//        }
//        return ans;
//    }
};
