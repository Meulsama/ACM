/*
    最坏: O(n ^ 2 * m)
    二分图最大匹配(单位网络——除源点、汇点外所有边的容量为1): O(m * sqrt(n))
*/
template<typename T>
struct Dinic {
    struct Edge {
        int from, to;
        T cap, flow;
    };

    int n, m, s, t;
    vector<int> d, cur;
    vector <vector<int>> G;
    vector<bool> vis;
    vector <Edge> edges;

    Dinic() : n(0) {}

    Dinic(int n) : n(n), d(n, 0), cur(n, 0), G(n), vis(n, false) {}

    void init(int n) {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void add(int from, int to, T cap, T incap = 0) {
        edges.push_back({from, to, cap, 0});
        edges.push_back({to, from, incap, 0});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool bfs() {
        vis.assign(n, false);
        queue<int> Q;
        d[s] = 0;
        vis[s] = true;
        Q.push(s);
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto v : G[u]) {
                Edge &e = edges[v];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = true;
                    d[e.to] = d[u] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    T dfs(int u, T w) {
        if (u == t || w == 0) return w;
        T flow = 0, f;
        for (int &i = cur[u]; i < G[u].size(); i++) {
            int v = G[u][i];
            Edge &e = edges[v];
            if (d[e.to] == d[u] + 1 && (f = dfs(e.to, min(w, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[v ^ 1].flow -= f;
                flow += f;
                w -= f;
                if (w == 0) break;
            }
        }
        return flow;
    }

    T Maxflow(int s, int t) {
        return Maxflow(s, t, numeric_limits<T>::max());
    }

    T Maxflow(int s, int t, T limit) {
        this->s = s;
        this->t = t;
        T maxflow = 0;
        while (bfs()) {
            cur.assign(n, 0);
            maxflow += dfs(s, limit);
        }
        return maxflow;
    }
};