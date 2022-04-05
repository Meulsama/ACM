vector<int> SCC_tarjan(int n, const vector<vector<int>>& E) {
    vector<pair<int, int>> p;
    vector<int> dfn(n), low(n), scc(n), stk;
    int dfnCnt = 0, sccCnt = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        stk.push_back(u);
        low[u] = dfn[u] = ++dfnCnt;
        for (auto v : E[u]) {
            if (!dfn[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
            } else if (!scc[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            int v;
            sccCnt++;
            do {
                v = stk.back();
                scc[v] = sccCnt;
                stk.pop_back();
            } while (v != u);
        }
    };
    for (int i = 0; i < n; i++) {
        if (!dfn[i]) dfs(i, -1);
    }
    return scc;
}