template <int NV> struct mcmf {
    const int64_t inf = 1ll << 60;
 
    struct edge {
        int v;
        int64_t cost, flow, cap;
    };
    vector<edge> E;
    vector<int> G[NV];
    int64_t d[NV], h[NV], f[NV], prev[NV];
    bool vis[NV];
 
    void init() {
        E.clear();
        for (int i = 0; i < NV; i++) {
            G[i].clear();
        }
    }
    void addedge(int u, int v, int64_t cap, int64_t cost) {
        E.push_back({ v, cost, 0, cap });
        G[u].push_back((int) E.size() - 1);
        E.push_back({ u, -cost, cap, cap });
        G[v].push_back((int) E.size() - 1);
    }
    void preprocess(int src, int dst) {
        // build array-h with Bellman-Ford
        fill(h, h + NV, 0);
    }
    // { cost, flow }
    pair<int64_t, int64_t> solve(int src, int dst, int64_t cap) {
        preprocess(src, dst);
        int64_t sum = 0, used = 0;
        while (used < cap) {
            fill(d, d + NV, inf);
            fill(prev, prev + NV, -1);
            fill(vis, vis + NV, false);
            priority_queue<pair<int64_t, int>> Q;
            d[src] = 0, f[src] = cap - used, Q.push({ 0, src });
            while (!Q.empty()) {
                int u = Q.top().second; Q.pop();
                if (vis[u]) {
                    continue;
                }
                vis[u] = true;
                for (int i : G[u]) {
                    const edge &e = E[i];
                    const int64_t w = E[i].cost + h[u] - h[e.v];
                    if (e.flow < e.cap && !vis[e.v] && d[e.v] > d[u] + w) {
                        d[e.v] = d[u] + w, prev[e.v] = i, f[e.v] = min(f[u], e.cap - e.flow);
                        Q.push({ -d[e.v], e.v });
                    }
                }
            }
            if (d[dst] == inf) {
                break;
            }
            for (int i = 0; i < NV; i++) {
                if (d[i] < inf) {
                    h[i] += d[i];
                }
            }
            used += f[dst], sum += h[dst] * f[dst];
            for (int x = dst; ~prev[x]; x = E[prev[x] ^ 1].v) {
                E[prev[x]].flow += f[dst], E[prev[x] ^ 1].flow -= f[dst];
            }
        }
        return { sum, used };
    }
};