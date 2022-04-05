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
    线性求逆元
*/

vector<int> inverse(int n, int p) {
    vector<int> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = 1ll * (p - p / i) * inv[p % i] % p;
    }
    return inv;
}