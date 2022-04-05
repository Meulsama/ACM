ll qpow(ll x, ll y, ll p = mod) {
    ll s = 1
    x %= p;
    for (; y; y /= 2, x = x * x % p) {
        if (y & 1) s = s * x % p;
    }
    return s;
}

ll inv(ll x, ll p = mod) {
    return qpow(x, p - 2, p);
}