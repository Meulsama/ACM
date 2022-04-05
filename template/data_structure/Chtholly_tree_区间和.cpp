struct node {
    int l, r;
    mutable ll v;
    node(const int &l, const int &r, const ll&v) : l(l), r(r), v(v) {}
    inline bool operator < (const node &T) const {
        return l < T.l;
    }
};

set<node> odt;

auto split(int x) {
    if (x > n) return odt.end();
    auto it = prev(odt.upper_bound({x, 0, 0}));
    if (it->l == x) return it;
    int l = it->l, r = it->r;
    ll v = it->v;
    odt.erase(it);
    odt.insert({l, x - 1, v});
    return odt.insert({x, r, v}).first;
}

void assign(int l, int r, ll v) {
    auto itr = split(r + 1), itl = split(l);
    odt.erase(itl, itr);
    odt.insert({l, r, v});
}

void add(int l, int r, ll v) {
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++) {
        it->v += v;
    }
}

ll kth(int l, int r, int k) {
    auto itr = split(r + 1);
    auto itl = split(l);
    vector<pair<ll, ll>> V;
    while (itl != itr) {
        V.push_back({itl->v, itl->r - itl->l + 1});
        itl++;
    }
    sort(V.begin(), V.end());
    for (auto [x, y] : V) {
        k -= y;
        if (k <= 0) return x;
    }
}

ll sum(int l, int r) {
    ll ans = 0;
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++) {
        ans += it->v;
    }
    return ans;
}

/*
i = l to r
ans = sum ai ^ x (mod y)
*/
ll power(int l, int r, ll x, ll y) {
    ll ans = 0;
    auto end = split(r + 1);
    for (auto it = split(l); it != end; it++) {
        ans = (ans + qpow(it->v, x, y) * (it->r - it->l + 1)) % y;
    }
    return ans;
}