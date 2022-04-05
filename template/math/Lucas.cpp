inline ll qpow(ll a, ll b, ll p = mod) {
    ll base = a % p;
    ll ans = 1;
    while (b > 0) {
        if (b & 1) ans = (ans * base) % p;
        base = base * base % p;
        b >>= 1;
    }
    return ans;
}

inline ll C(ll n, ll m, ll p = mod) {
    if (n < m) return 0;//组合数n<m特判
    if (m > n - m) m = n - m;//组合数性质
    ll a = 1, b = 1;
    for (int i = 0; i < m; i++) {
        a = (a * (n - i) % p);//组合数分子 a 
        b = (b * (i + 1)) % p;//组合数分母 b
    }
    return a * qpow(b, p - 2) % p;//费马小定理 a/b=a*b^(p-2) 
}

inline ll Lucas(ll n, ll m, ll p = mod) {
    return m == 0 ? 1 : Lucas(n / p, m / p) * C(n % p, m % p) % p;
}
