vector<ll> fac, ifac;

ll qpow(ll a, ll b) {
    ll res = 1;
    for (; b > 0; a = a * a % mod, b /= 2) {
        if (b & 1) res = res * a % mod;
    }
    return res;
}

ll perm(ll x, ll y) { return y > x || y < 0 ? 0 : fac[x] * ifac[x - y] % mod; }

ll comb(ll x, ll y) { return y > x || y < 0 ? 0 : perm(x, y) * ifac[y] % mod; }

void init(int n) {
    fac.resize(n);
    ifac.resize(n);
    fac[0] = 1;
    for (int i = 1; i < n; i++) fac[i] = 1ll * i * fac[i - 1] % mod;
    ifac[n - 1] = qpow(fac[n - 1], mod - 2);
    for (int i = n - 1; i; i--) ifac[i - 1] = 1ll * i * ifac[i] % mod;
}