#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 5e5 + 5;

int n, m, s, deep[N], f[N][21], lg[N];
vector<int> G[N];

void dfs(int u, int fa) {
    f[u][0] = fa;
    deep[u] = deep[fa] + 1;
    for (auto v:G[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}

void ST(int n) {
    for (int j = 1; j <= 19; j++)
        for (int i = 1; i <= n; i++)
            f[i][j] = f[f[i][j - 1]][j - 1];
}

int LCA(int u, int v) {
    if (deep[u] < deep[v]) swap(u, v);
    int h = deep[u] - deep[v];
    for (int i = 0; i < 20; i++)
        if (h & (1 << i)) u = f[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if ((1 << i) <= deep[u] && f[u][i] != f[v][i]) {
            u = f[u][i];
            v = f[v][i];
        }
    }
    return f[u][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs(s, 0);
    ST(n);
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << '\n';
    }
    return 0;
}