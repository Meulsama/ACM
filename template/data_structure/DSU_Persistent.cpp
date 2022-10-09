struct PersistentDSU {
  vector<int> f, sz;
  vector<pair<int, int>> operations;
  int n;

  PersistentDSU(int n) : n(n), f(n), sz(n, 1) { iota(f.begin(), f.end(), 0); }

  int find(int x) {
    while (x != f[x]) {
      x = f[x];
    }
    return x;
  }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
      return false;
    }
    if (sz[x] > sz[y]) {
      swap(x, y);
    }
    operations.emplace_back(x, f[x]);
    f[x] = y;
    operations.emplace_back(~y, sz[y]);
    sz[y] += sz[x];
    return true;
  }

  int getSize(int x) { return sz[find(x)]; }

  void rollback(int T) {
    while ((int)operations.size() > T) {
      auto [u, v] = operations.back();
      operations.pop_back();
      if (u >= 0) {
        f[u] = v;
      } else {
        sz[~u] = v;
      }
    }
  }
};