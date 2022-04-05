/*
时间复杂度:O(n + m)
返回一个[1, sccCnt]的缩点后编号
*/
vector<int> SCC_kosaraju(int n, const vector<vector<int>>& E1) {
    vector<vector<int>> E2(n);
    for (int i = 0; i < n; i++) for (auto j : E1[i]) E2[j].push_back(i);
    vector<int> q;
    vector<bool> used(n);
    function<void(int)> dfs1 = [&](int u) {
        used[u] = true;
        for (auto v : E1[u]) if (!used[v]) dfs1(v);
        q.push_back(u);
    };
    int sccCnt = 0;
    vector<int> scc(n);
    function<void(int)> dfs2 = [&](int u) {
        scc[u] = sccCnt;
        for (auto v : E2[u]) if (!scc[v]) dfs2(v);
    };
    for (int i = 0; i < n; i++) if (!used[i]) dfs1(i);
    for (int i = n - 1; i >= 0; i--) if (!scc[q[i]]) {
        sccCnt++;
        dfs2(q[i]);
    }
    return scc;
}