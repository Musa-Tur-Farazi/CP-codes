
mt19937 rnd(sync_clock);
const int P = 1e6 + 9;
int seq[P];
int primes[P], spf[P];
inline int add_mod(int x, int y, int m) { return (x += y) < m ? x : x - m; }
inline int mul_mod(int x, int y, int m) { int res = __int128(x) * y % m; return res; }
inline int pow_mod(int x, int n, int m) {
    int res = 1 % m;
    for (; n; n >>= 1) { if (n & 1) res = mul_mod(res, x, m); x = mul_mod(x, x, m); }
    return res;
}
  // O(it * (logn)^3), it = number of rounds performed
inline bool miller_rabin(int n) {
    if (n <= 2 || (n & 1 ^ 1)) return (n == 2);
    if (n < P) return spf[n] == n;
    int c, d, s = 0, r = n - 1;
    for (; !(r & 1); r >>= 1, s++) {}
        // each iteration is a round
    for (int i = 0; primes[i] < n && primes[i] < 32; i++) {
        c = pow_mod(primes[i], r, n);
        for (int j = 0; j < s; j++) {
            d = mul_mod(c, c, n);
            if (d == 1 && c != 1 && c != (n - 1)) return false;
            c = d;
        }
        if (c != 1) return false;
    }
    return true;
}
void init() {
    int cnt = 0;
    for (int i = 2; i < P; i++) {
        if (!spf[i]) primes[cnt++] = spf[i] = i;
        for (int j = 0, k; (k = i * primes[j]) < P; j++) {
            spf[k] = primes[j];
            if (spf[i] == spf[k]) break;
        }
    }
}
    // returns O(n^(1/4))
int pollard_rho(int n) {
    while (1) {
        int x = rnd() % n, y = x, c = rnd() % n, u = 1, v, t = 0;
        int *px = seq, *py = seq;
        while (1) {
            *py++ = y = add_mod(mul_mod(y, y, n), c, n);
            *py++ = y = add_mod(mul_mod(y, y, n), c, n);
            if ((x = *px++) == y) break;
            v = u;
            u = mul_mod(u, abs(y - x), n);
            if (!u) return __gcd(v, n);
            if (++t == 32) {
                t = 0;
                if ((u = __gcd(u, n)) > 1 && u < n) return u;
            }
        }
        if (t && (u = __gcd(u, n)) > 1 && u < n) return u;
    }
}
vector<int>factorize(int n) {
    if (n == 1) return vector <int>();
    if (miller_rabin(n)) return vector<int> {n};
    vector <int> v, w;
    while (n > 1 && n < P) {
        v.push_back(spf[n]);
        n /= spf[n];
    }
    if (n >= P) {
        int x = pollard_rho(n);
        v = factorize(x);
        w = factorize(n / x);
        v.insert(v.end(), w.begin(), w.end());
    }
    return v;
}

vector<pair<int,int>>idxfactor(int n){
    auto it = factorize(n);
    vector<pair<int,int>>v;
    int k = it.size();
    for(int i=0;i<k;i++){
        if(it[i]==it[i+1] && i+1 < k){
            int cnt = 1;
            while(it[i]==it[i+1]){ cnt++; i++; }
            v.push_back({it[i],cnt});
        }
        else v.push_back({it[i],1});
    }
    return v;
}
