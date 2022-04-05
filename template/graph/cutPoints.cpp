auto cutPoints(int n, const vector<vector<int>>& E) {
    vector<int> low(n), dfn(n);
    vector<bool> cut(n);
    int timeStamp = 0;
    function<void(int, int)> dfs = [&](int u, int p) {
        low[u] = dfn[u] = ++timeStamp;
        int cnt = 0;
        for (auto v : E[u]) {
            if (!dfn[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                cnt++;
                if (low[v] >= dfn[u] && ~p) cut[u] = true;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (p == -1 && cnt > 1) cut[u] = true;
    };
    for (int i = 0; i < n; i++) if (!dfn[i]) dfs(i, -1);
    vector<int> res;
    for (int i = 0; i < n; i++) if (cut[i]) res.push_back(i);
    return res;
}