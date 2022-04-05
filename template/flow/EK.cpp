// O(n * m ^ 2)

struct Edge {
    int from, to, cap, flow;
    Edge(int from, int to, int cap, int flow) : from(from), to(to), cap(cap), flow(flow) {}
};

struct EK {
    int n, m;
    vector<Edge> edges;
    vector<int> G[N];
    int a[N], p[N];

    void init(int n) {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from, int to, int cap) {
        edges.push_back({from, to, cap, 0});
        edges.push_back({to, from, 0, 0});
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }

    bool bfs(int s, int t) {
        memset(a, 0, sizeof(a));
        queue<int> Q;
        Q.push(s);
        a[s] = INF;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            for (auto v : G[u]) {
                Edge& e = edges[v];
                if (!a[e.to] && e.cap > e.flow) {
                    p[e.to] = v;
                    a[e.to] = min(a[u], e.cap - e.flow);
                    Q.push(e.to);
                }
            }
            if (a[t]) break;
        }
        return a[t];
    }

    int Maxflow(int s, int t) {
        int maxflow = 0;
        while (bfs(s, t)) {
            maxflow += a[t];
            for (int i = t; i != s; i = edges[p[i]].from) {
                edges[p[i]].flow += a[t];
                edges[p[i] ^ 1].flow -= a[t];
            }
        }
        return maxflow;
    }
};