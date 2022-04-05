#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int INF = 1e9;
constexpr ll N = 1e6 + 5;

int rt[N], tot;

struct node {
    int l, r, cnt;
} t[N << 5];

void modify(int &x, int l, int r, int v) {
    t[++tot] = t[x];
    x = tot;
    t[x].cnt++;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (v <= mid) modify(t[x].l, l, mid, v);
    else modify(t[x].r, mid + 1, r, v);
}

int query(int x, int y, int l, int r, int v) {
    if (l == r) return l;
    int mid = (l + r) >> 1, cnt = t[t[y].l].cnt - t[t[x].l].cnt;
    if (v <= cnt) return query(t[x].l, t[y].l, l, mid, v);
    else return query(t[x].r, t[y].r, mid + 1, r, v - cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        modify(rt[i] = rt[i - 1], -INF, INF, x);
    }
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << query(rt[l - 1], rt[r], -INF, INF, k) << '\n';
    }
    return 0;
}