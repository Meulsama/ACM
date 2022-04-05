#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll N = 1e5 + 5;

#define ls (p << 1)
#define rs (ls | 1)
#define tm ((tl + tr) >> 1)

struct node {
    int l, r, cnt;
    ll sum;
} t[N << 5];

int tot, rt[N];

void modify(int &x, int l, int r, int v) {
    t[++tot] = t[x];
    x = tot;
    t[x].cnt++;
    t[x].sum += v;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (v <= mid) modify(t[x].l, l, mid, v);
    else modify(t[x].r, mid + 1, r, v);
}

ll query(int x, int y, int l, int r, int v) {
    if (l == r) return 1ll * v * l;
    int mid = (l + r) >> 1, cnt = t[t[y].r].cnt - t[t[x].r].cnt;
    if (v <= cnt) return query(t[x].r, t[y].r, mid + 1, r, v);
    else return query(t[x].l, t[y].l, l, mid, v - cnt) + t[t[y].r].sum - t[t[x].r].sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);
    int T;
    cin >> T;
    while (T--) {
        tot = 0;
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            modify(rt[i] = rt[i - 1], 1, 1000000, x);
        }
        int m;
        cin >> m;
        while (m--) {
            int l, r, k;
            cin >> l >> r >> k;
            int x = r - l + 1;
            cout << 1ll * x * (x + 1) * (2 * x + 1) / 6 + query(rt[l - 1], rt[r], 1, 1000000, k) << '\n';
        }
    }
    return 0;
}