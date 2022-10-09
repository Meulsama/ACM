/*
    n = 点数
    O(n ^ 2)
*/
template <typename T>
struct Dijkstra {
  int n;
  vector<vector<T>> e;
  vector<T> d;
  vector<bool> used;
  vector<int> from;

  Dijkstra(const int _n, const vector<vector<T>>& _e) : n(_n), e(_e) {}

  vector<T> shortestPath(int s) {
    d.assign(n, -1);
    used.assign(n, false);
    from.assign(n, -1);
    d[s] = 0;
    for (int i = 0; i < n; i++) {
      int u = -1;
      for (int v = 0; v < n; v++) {
        if (!used[v] && d[v] != -1 && (u == -1 || d[v] < d[u])) {
          u = v;
        }
      }
      if (u == -1) {
        break;
      }
      used[u] = true;
      for (int v = 0; v < n; v++) {
        if (e[u][v] == -1) continue;
        if (d[v] == -1 || d[v] > d[u] + e[u][v]) {
          from[v] = u;
          d[v] = d[u] + e[u][v];
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