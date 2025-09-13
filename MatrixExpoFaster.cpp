const int FACTORIAL = 2e5+7;
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

lint _fact[FACTORIAL];
lint _invfact[FACTORIAL];
lint _inv[FACTORIAL];

void init(int m) {    /*call*/
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

struct Mat {
    lint mat[2][2];
    Mat friend operator *(const Mat &a,const Mat &b){
        Mat c;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                c.mat[i][j] = 0;
                for(int k=0;k<2;k++){
                    c.mat[i][j]+=(a.mat[i][k]*b.mat[k][j]);
                }
            }
        }
        return c;
    }
};

Mat dp[31];
void calc(){
    Mat base{{{0,1},{1,1}}};
    Mat res{{{1,0},{0,1}}};
    dp[0] = res;
    dp[1] = base;
    for(int i=2;i<31;i++){
        base=base*base;
        dp[i] = base;
    }
}

Mat fastpow(Mat &base,int n){
    Mat res{{{1,0},{0,1}}};
    int i = 0;
    while(n){
        if(n&1LL) res=res*dp[i+1];
        i++;
        n>>=1LL;
    }
    return res;
}
//f(n) = af(n-1)+bf(n-2)+... then C = [{0 1 0 0 0 ..},{0,0,1,...}..{a b c ..}] ans = C[n][n]
lint fib(int n){
    Mat v{{{0,1},{1,1}}};
    return fastpow(v,n).mat[0][1];
}
