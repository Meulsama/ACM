/*
    m = 边数
    O(mlogm)
*/
template<typename U = int, typename T = ll>
struct Dijkstra {
    int n;
    vector<vector<pair<int, U>>> e;
    vector<T> d;
    vector<int> from;

    Dijkstra(const int _n, const vector<vector<pair<int, U>>> &_e) : n(_n), e(_e) {}

    vector<T> shortestPath(int s) {
        d.assign(n, -1);
        from.assign(n, -1);
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
        q.emplace(d[s] = 0, s);
        while (!q.empty()) {
            auto[_, u] = q.top();
            q.pop();
            if (_ > d[u]) continue;
            for (auto& [v, w] : e[u]) {
                if (d[v] == -1 || d[v] > d[u] + w) {
                    from[v] = u;
                    q.emplace(d[v] = d[u] + w, v);
                }
            }
        }
        return d;
    }

    vector<int> getPath(int s, int t) {
        assert(s >= 0 && s < n);
        assert(t >= 0 && t < n);
        shortestPath(s);
        assert(d[t] != -1);
        vector<int> path;
        int i = t;
        do {
            path.emplace_back(i);
            i = from[i];
        } while (i != -1);
        reverse(path.begin(), path.end());
        return path;
    }
};