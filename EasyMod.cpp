//https://github.com/the-tourist/algo/blob/master/numeric/mint.cpp
template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <typename T>
class Modulo {
public:
    using Type = typename decay<decltype(T::value)>::type;
    constexpr Modulo() : value() {}
    template <typename U>
    Modulo(const U& x) {
        value = normalize(x);
    }
    template <typename U>
    static Type normalize(const U& x) {
        Type v;
        if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
        else v = static_cast<Type>(x % mod());
        if (v < 0) v += mod();
        return v;
    }
    const Type& operator()() const { return value; }
    template <typename U>
    explicit operator U() const { return static_cast<U>(value); }
    constexpr static Type mod() { return T::value; }

    Modulo& operator+=(const Modulo& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
    Modulo& operator-=(const Modulo& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
    template <typename U> Modulo& operator+=(const U& other) { return *this += Modulo(other); }
    template <typename U> Modulo& operator-=(const U& other) { return *this -= Modulo(other); }
    Modulo& operator++() { return *this += 1; }
    Modulo& operator--() { return *this -= 1; }
    Modulo operator++(int) { Modulo result(*this); *this += 1; return result; }
    Modulo operator--(int) { Modulo result(*this); *this -= 1; return result; }
    Modulo operator-() const { return Modulo(-value); }

    template <typename U = T>
    typename enable_if<is_same<typename Modulo<U>::Type, int>::value, Modulo>::type& operator*=(const Modulo& rhs) {
        value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
        return *this;
    }
    template <typename U = T>
    typename enable_if<is_same<typename Modulo<U>::Type, long long>::value, Modulo>::type& operator*=(const Modulo& rhs) {
        long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
        value = normalize(value * rhs.value - q * mod());
        return *this;
    }
    template <typename U = T>
    typename enable_if<!is_integral<typename Modulo<U>::Type>::value, Modulo>::type& operator*=(const Modulo& rhs) {
        value = normalize(value * rhs.value);
        return *this;
    }

    Modulo& operator/=(const Modulo& other) { return *this *= Modulo(inverse(other.value, mod())); }

    friend const Type& abs(const Modulo& x) { return x.value; }

    template <typename U>
    friend bool operator==(const Modulo<U>& lhs, const Modulo<U>& rhs);

    template <typename U>
    friend bool operator<(const Modulo<U>& lhs, const Modulo<U>& rhs);

    template <typename V, typename U>
    friend V& operator>>(V& stream, Modulo<U>& number);

private:
    Type value;
};

template <typename T> bool operator==(const Modulo<T>& lhs, const Modulo<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modulo<T>& lhs, U rhs) { return lhs == Modulo<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modulo<T>& lhs, const Modulo<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modulo<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modulo<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modulo<T>& lhs, const Modulo<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modulo<T> operator+(const Modulo<T>& lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) += rhs; }
template <typename T, typename U> Modulo<T> operator+(const Modulo<T>& lhs, U rhs) { return Modulo<T>(lhs) += rhs; }
template <typename T, typename U> Modulo<T> operator+(U lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) += rhs; }

template <typename T> Modulo<T> operator-(const Modulo<T>& lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) -= rhs; }
template <typename T, typename U> Modulo<T> operator-(const Modulo<T>& lhs, U rhs) { return Modulo<T>(lhs) -= rhs; }
template <typename T, typename U> Modulo<T> operator-(U lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) -= rhs; }

template <typename T> Modulo<T> operator*(const Modulo<T>& lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) *= rhs; }
template <typename T, typename U> Modulo<T> operator*(const Modulo<T>& lhs, U rhs) { return Modulo<T>(lhs) *= rhs; }
template <typename T, typename U> Modulo<T> operator*(U lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) *= rhs; }

template <typename T> Modulo<T> operator/(const Modulo<T>& lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) /= rhs; }
template <typename T, typename U> Modulo<T> operator/(const Modulo<T>& lhs, U rhs) { return Modulo<T>(lhs) /= rhs; }
template <typename T, typename U> Modulo<T> operator/(U lhs, const Modulo<T>& rhs) { return Modulo<T>(lhs) /= rhs; }

template<typename T, typename U>
Modulo<T> power(const Modulo<T>& a, const U& b) {
    assert(b >= 0);
    Modulo<T> x = a, res = 1;
    U p = b;
    while (p > 0) {
        if (p & 1) res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}

template <typename T>
bool IsZero(const Modulo<T>& number) {
    return number() == 0;
}

template <typename T>
string to_string(const Modulo<T>& number) {
    return to_string(number());
}

template <typename U, typename T>
U& operator<<(U& stream, const Modulo<T>& number) {
    return stream << number();
}

template <typename U, typename T>
U& operator>>(U& stream, Modulo<T>& number) {
    typename common_type<typename Modulo<T>::Type, long long>::type x;
    stream >> x;
    number.value = Modulo<T>::normalize(x);
    return stream;
}

/*
using ModType = int;

struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modulo<VarMod>;
*/

using lint = Modulo<std::integral_constant<decay<decltype(mod)>::type, mod>>;

vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

//Mint C(int n, int k) {
//    if (k < 0 || k > n) {
//        return 0;
//    }
//    while ((int) fact.size() < n + 1) {
//        fact.push_back(fact.back() * (int) fact.size());
//        inv_fact.push_back(1 / fact.back());
//    }
//    return fact[n] * inv_fact[k] * inv_fact[n - k];
//}
