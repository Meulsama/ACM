#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll N = 1e6 + 5;

int tot, rt[N];

struct node {
    int l, r;
    ll sum;
} t[N << 5];

void modify(int &x, int l, int r, int v) {
    t[++tot] = t[x];
    x = tot;
    t[x].sum += v;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (v <= mid) modify(t[x].l, l, mid, v);
    else modify(t[x].r, mid + 1, r, v);
}

ll query(int x, int y, int l, int r, ll v) {
    if (l == r) return t[y].sum - t[x].sum;
    int mid = (l + r) >> 1;
    if (v <= mid) return query(t[x].l, t[y].l, l, mid, v);
    else return query(t[x].r, t[y].r, mid + 1, r, v) + t[t[y].l].sum - t[t[x].l].sum;
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
        modify(rt[i] = rt[i - 1], 1, 1000000000, x);
    }
    int l, r;
    ll ans = 0;
    while (m--) {
        cin >> l >> r;
        l = (l + ans) % n + 1;
        r = (r + ans) % n + 1;
        if (l > r) swap(l, r);
        ans = 0;
        while (true) {
            ll res = query(rt[l - 1], rt[r], 1, 1000000000, ans + 1);
            if (res == ans) break;
            ans = res;
        }
        cout << ++ans << '\n';
    }
    return 0;
}