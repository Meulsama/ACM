#include<bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const double eps = 1e-8;
const int NINF = 0xc0c0c0c0;
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
const ll N = 2e4 + 5;

int n, m, cnt, low[N], dfn[N], cut[N];
vector<int> G[N];

void tarjan(int x, int fa) {
    low[x] = dfn[x] = ++cnt;
    int son = 0;
    for (auto c:G[x]) {
        if (!dfn[c]) {
            tarjan(c, fa);
            low[x] = min(low[x], low[c]);
            if (low[c] >= dfn[x] && x != fa) cut[x] = true;
            if (x == fa) son++;
        } else low[x] = min(low[x], dfn[c]);
    }
    if (son >= 2 && x == fa) cut[x] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i, i);
    int tot = 0;
    for (int i = 1; i <= n; i++)
        if (cut[i])
            tot++;
    cout << tot << '\n';
    for (int i = 1; i <= n; i++)
        if (cut[i])
            cout << i << " ";
    return 0;
}