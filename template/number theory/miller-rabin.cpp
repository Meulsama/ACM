ll qpow(ll a, ll n, ll p) {
    ll ans = 1;
    while (n) {
        if (n & 1)
            ans = (__int128)ans * a % p;
        a = (__int128)a * a % p;
        n >>= 1;
    }
    return ans;
}
 
bool is_prime(ll x) {
    if (x < 3) return x == 2;
    if (x % 2 == 0) return false;
    ll A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, d = x - 1, r = 0;
    while (d % 2 == 0) d /= 2, ++r;
    for (int k = 0; k < 7; k++) {
        ll a = A[k];
        ll v = qpow(a, d, x);
        if (v <= 1 || v == x - 1) continue;
        for (int i = 0; i < r; ++i) {
            v = (__int128)v * v % x;
            if (v == x - 1 && i != r - 1) {
                v = 1;
                break;
            }
            if (v == 1) return false;
        }
        if (v != 1) return false;
    }
    return true;
}