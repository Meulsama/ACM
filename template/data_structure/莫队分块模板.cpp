#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const double eps = 1e-8;
const int NINF = 0xc0c0c0c0;
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;
const ll N = 1e6 + 5;

int n, q, a[N], x, y, l = 1, r, p[N], ans[N], sq, belong[N], num;

struct node {
    int l, r, bel;

    bool operator<(const node &T) const {
        return (belong[l] ^ belong[T.l]) ? belong[l] < belong[T.l] : ((belong[l] & 1) ? r < T.r : r > T.r);
    }
} querry[N];

int cmp(node a, node b) {
    if (a.l / sq != b.l / sq)return a.l / sq < b.l / sq;
    return a.r / sq < b.r / sq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) cin >> x >> y, querry[i] = {x, y, i};
    sq = sqrt(n);
    for (int i = 1; i <= n; i++) belong[i] = min(sq, (i - 1) / sq + 1);
    sort(querry + 1, querry + 1 + q);
    for (int i = 1; i <= q; i++) {
        while (querry[i].l < l) num += !p[a[--l]]++;
        while (querry[i].l > l) num -= !--p[a[l++]];
        while (querry[i].r < r) num -= !--p[a[r--]];
        while (querry[i].r > r) num += !p[a[++r]]++;
        ans[querry[i].bel] = num;
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}