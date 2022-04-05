#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll N = 1e6 + 5;

int low[N], dfn[N], bridge[N], cntBridge, dfsClock;
vector<int> G[N];

void tarjan(int u, int fa) {
    f[u] = fa;
    low[u] = dfn[u] = ++dfsClock;
    for (auto v:G[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) bridge[v] = true, cntBridge++;
        } else if (dfn[v] < dfn[u] && v != fa) low[u] = min(low[u], dfn[v]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}