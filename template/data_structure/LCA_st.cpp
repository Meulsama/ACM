#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N = 5e5 + 5;

int n, m, s, deep[N << 1], id[N], timeStamp = -1;
vector<int> a;
vector<int> e[N];

void dfs(int u, int p, int d) {
    a.push_back(u);
    id[u] = ++timeStamp;
    deep[timeStamp] = d;
    for (auto v : e[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
        a.push_back(u);
        deep[++timeStamp] = d;
    }
}

template <typename T, class F = function<T(const T&, const T&)>>
struct SparseTable {
    int n;
    vector<vector<T>> mat;
    F func;

    SparseTable(const vector<T>& a, const F& f) : func(f) {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        mat.resize(max_log);
        mat[0] = a;
        for (int j = 1; j < max_log; j++) {
            mat[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T get(int from, int to) const {
        from = id[from];
        to = id[to];
        if (from > to) swap(from, to);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return a[func(mat[lg][from], mat[lg][to - (1 << lg) + 1])];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);
    cin >> n >> m >> s;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(s, 0, 1);
    vector<int> p(a.size());
    iota(p.begin(), p.end(), 0);
    SparseTable<int> st(p, [&](int i, int j) { return deep[i] < deep[j] ? i : j; });
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        cout << st.get(u, v) << '\n';
    }
    return 0;
}