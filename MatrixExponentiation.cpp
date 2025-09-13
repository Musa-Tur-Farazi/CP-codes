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
//f(n) = af(n-1)+bf(n-2)+... then C = [{0 1 0 0 0 ..},{0,0,1,...}..{a b c ..}] ans = C[n][n]
