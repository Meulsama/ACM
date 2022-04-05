template<typename T>
T exgcd(T a, T b, T &x, T &y) {
    if (!b) { x = 1, y = 0; return a; }
    T d = exgcd(b, a % b, x, y);
    T z = x;
    x = y, y = z - y * (a / b);
    return d;
}

template<typename T>
T inv(T a, T p) {
    T x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

/*
    arbitrarily i, j: gcd(m_i, m_j) = 1
*/

ll CRT(const vector<ll> &r, const vector<ll> &m) {
    assert(r.size() == m.size());
    int n = int(r.size());
    ll x = 0, p = 1;
    for (int i = 0; i < n; i++) p *= m[i];
    for (int i = 0; i < n; i++) {
        ll t = p / m[i];
        x = (x + r[i] * t * inv(t, m[i])) % p;
    }
    return x;
}