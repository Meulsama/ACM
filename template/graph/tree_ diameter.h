int diam, d[N];
vector<int> G[N];

int dfs(int u, int p) {
    int len = 0;
    for (auto v : G[u]) {
        if (v != p) {
            d[v] = d[u] + 1;
            int cur = dfs(v, u) + 1;
            diam = max(diam, cur + len);
            len = max(len, cur);
        }
    }
    return len;
}

int diam, d[N], f[N];
vector<int> G[N];

void dfs(int u, int p) {
    f[u] = 0;
    for (auto v:G[u]) {
        if (v != p) {
            d[v] = d[u] + 1;
            dfs(v, u);
            diam = max(diam, f[u] + f[v] + 1);
            f[u] = max(f[u], f[v] + 1);
        }
    }
}