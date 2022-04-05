#include <bits/stdc++.h>

using i64 = long long;

struct Flow {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to, cap;
        Edge(int to, int cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
    Flow(int n) : n(n), g(n) {}
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int i : g[u]) {
                int v = e[i].to;
                int c = e[i].cap;
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t)
                        return true;
                    que.push(v);
                }
            }
        }
        return false;
    }
    int dfs(int u, int t, int f) {
        if (u == t)
            return f;
        int r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            int j = g[u][i];
            int v = e[j].to;
            int c = e[j].cap;
            if (c > 0 && h[v] == h[u] + 1) {
                int a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0)
                    return f;
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, int c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    int maxFlow(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, INF);
        }
        return ans;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int m;
    std::cin >> m;
    
    std::vector<std::vector<int>> a(m);
    std::vector<int> v;
    for (int i = 0; i < m; i++) {
        int n;
        std::cin >> n;
        
        a[i].resize(n);
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
            v.push_back(a[i][j]);
        }
    }
    
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    
    int nv = v.size();
    
    std::vector<std::string> ans(m);
    
    std::vector<int> cnt(nv);
    
    for (int i = 0; i < m; i++) {
        int n = a[i].size();
        ans[i].resize(n, 'L');
        for (int j = 0; j < n; j++) {
            a[i][j] = std::lower_bound(v.begin(), v.end(), a[i][j]) - v.begin();
            cnt[a[i][j]]++;
        }
    }
    
    for (int i = 0; i < nv; i++) {
        if (cnt[i] % 2 != 0) {
            std::cout << "NO\n";
            return 0;
        }
    }
    
    Flow flow(m + nv + 2);
    int source = m + nv, sink = source + 1;
    
    int tot = 0;
    
    std::vector<std::vector<int>> e(m);
    for (int i = 0; i < m; i++) {
        int n = a[i].size();
        e[i].resize(n);
        tot += n;
        flow.addEdge(source, i, n / 2);
        for (int j = 0; j < n; j++) {
            e[i][j] = flow.e.size();
            flow.addEdge(i, m + a[i][j], 1);
        }
    }
    for (int i = 0; i < nv; i++) {
        flow.addEdge(m + i, sink, cnt[i] / 2);
    }
    
    if (flow.maxFlow(source, sink) != tot / 2) {
        std::cout << "NO\n";
        return 0;
    }
    
    std::cout << "YES\n";
    for (int i = 0; i < m; i++) {
        int n = a[i].size();
        for (int j = 0; j < n; j++) {
            if (flow.e[e[i][j] + 1].cap > 0) {
                ans[i][j] = 'R';
            }
        }
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}