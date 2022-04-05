int qpow(ll x, ll y, ll p = mod) {
    x %= p;
    ll res = 1;
    while (y > 0) {
        if (y & 1) res = res * x % p;
        x = x * x % p;
        y >>= 1;
    }
    return res;
}

int bsgs(int a, int b, int p = mod) {
    if (b == 1) return 0;
    unordered_map<int, int> H;
    H.reserve(sqrt(p));
    b %= p;
    int block = sqrt(p) + 1;
    for (int i = 0, x = b; i < block; i++) {
        H[x % p] = i;
        x = 1ll * x * a % p;
    }
    int A = qpow(a, block, p);
    if (!A) return b == 0 ? 1 : -1;
    for (int i = 1, x = A; i <= block; i++) {
        if (H.count(x)) return 1ll * i * block - H[x];
        x = 1ll * x * A % p;
    }
    return -1;
}