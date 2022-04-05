ll qpow(ll a, ll b, ll p = mod) {
    ll res = 1;
    a %= p;
    while (b > 0) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

struct ChothollyTree {
    map <int, ll> odt;

    auto split(int x) {
        auto it = prev(odt.upper_bound(x));
        if (it->first != x) {
            odt[x] = it->second;
            ++it;
        }
        return it;
    }

    void add(int l, int r, ll v) {
        auto end = split(r + 1);
        for (auto it = split(l); it != end; it++)
            it->second += v;
    }

    void assign(int l, int r, ll v) {
        auto end = split(r + 1), begin = split(l);
        odt.erase(begin, end);
        odt[l] = v;
    }

    ll kth(int l, int r, int k) {
        auto itr = split(r + 1), itl = split(l);
        vector<pair<ll,ll> > V;
        for (int R; itl != itr;) {
            R = (itr--)->first;
            V.emplace_back(itr->second, R - itr->first);
        }
        sort(V.begin(), V.end());
        for (auto [x, y] : V) {
            k -= y;
            if (k <= 0) return x;
        }
    }

    ll sum(int l, int r) {
        ll res = 0;
        auto itr = split(r + 1), itl = split(l);
        for (int R; itl != itr;) {
            R = (itr--)->first;
            res = (res + itr->second * (R - itr->first));
        }
        return res;
    }

    ll power(int l, int r, ll x, ll y) {
        ll res = 0;
        auto itr = split(r + 1), itl = split(l);
        for (int R; itl != itr;) {
            R = (itr--)->first;
            res = (res + qpow(itr->second, x, y) * (R - itr->first)) % y;
        }
        return res;
    }
};