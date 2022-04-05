template<typename T = int>
struct DSU {
    int n;
    vector<T> f, sz;
    DSU(int n) : n(n), f(n), sz(n, 1) { iota(f.begin(), f.end(), 0); }

    int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] > sz[y]) swap(x, y);
        sz[y] += sz[x];
        f[x] = y;
        return true;
    }

    int size(int x) { return sz[find(x)]; }
};