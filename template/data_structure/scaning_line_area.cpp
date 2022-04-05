#include <bits/stdc++.h>
#define ls (p << 1)
#define rs (ls | 1)
#define tm ((tl + tr) >> 1)

using namespace std;
using ll = long long;
constexpr ll N = 2e6 + 5;

struct line {
    int l, r, h, op;

    inline bool operator<(const line &T) const {
        return h == T.h ? op > T.op : h < T.h;
    }
} a[N];

int n, m, x[N], cnt[N << 2], len[N << 2];

void push_up(int p, int tl, int tr) {
    if (cnt[p]) {
        len[p] = x[tr] - x[tl];
    } else {
        len[p] = len[ls] + len[rs];
    }
}

void modify(int p, int tl, int tr, int L, int R, int v) {
    if (x[tr] <= L || R <= x[tl]) return;
    if (L <= x[tl] && x[tr] <= R) {
        cnt[p] += v;
        push_up(p, tl, tr);
        return;
    }
    if (L <= x[tm]) modify(ls, tl, tm, L, R, v);
    if (R > x[tm]) modify(rs, tm, tr, L, R, v);
    push_up(p, tl, tr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a[++m] = {x1, x2, y1, 1};
        x[m] = x1;
        a[++m] = {x1, x2, y2, -1};
        x[m] = x2;
    }
    n = m;
    sort(a + 1, a + 1 + n);
    sort(x + 1, x + 1 + n);
    m = unique(x + 1, x + 1 + n) - (x + 1);
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        modify(1, 1, m, a[i].l, a[i].r, a[i].op);
        ans += 1ll * len[1] * (a[i + 1].h - a[i].h);
    }
    cout << ans << '\n';

    return 0;
}