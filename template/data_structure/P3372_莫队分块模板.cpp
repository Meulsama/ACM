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
const ll N = 1e5 + 5;

int n, m, st[N], ed[N], siz[N], bel[N], sq;
ll a[N], sum[N], mark[N];

void init() {
    sq = sqrt(n);
    for (int i = 1; i <= sq; i++) {
        st[i] = n / sq * (i - 1) + 1;
        ed[i] = n / sq * i;
    }
    ed[sq] = n;
    for (int i = 1; i <= sq; i++) {
        siz[i] = ed[i] - st[i] + 1;
        for (int j = st[i]; j <= ed[i]; j++) {
            bel[j] = i;
            sum[i] += a[j];
        }
    }
}

inline void add(int L, int R, int K) {
    if (bel[L] == bel[R]) {
        for (int i = L; i <= R; i++) {
            a[i] += K;
            sum[bel[i]] += K;
        }
    } else {
        for (int i = L; i <= ed[bel[L]]; i++) {
            a[i] += K;
            sum[bel[i]] += K;
        }
        for (int i = bel[L] + 1; i < bel[R]; i++) {
            mark[i] += K;
        }
        for (int i = st[bel[R]]; i <= R; i++) {
            a[i] += K;
            sum[bel[i]] += K;
        }
    }
}

inline ll getSum(int L, int R) {
    ll ans = 0;
    if (bel[L] == bel[R]) {
        for (int i = L; i <= R; i++) {
            ans += a[i] + mark[bel[L]];
        }
    } else {
        for (int i = L; i <= ed[bel[L]]; i++) {
            ans += a[i] + mark[bel[L]];
        }
        for (int i = bel[L] + 1; i < bel[R]; i++) {
            ans += sum[i] + mark[i] * siz[i];
        }
        for (int i = st[bel[R]]; i <= R; i++) {
            ans += a[i] + mark[bel[R]];
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    init();
    while (m--) {
        int t, x, y, k;
        cin >> t >> x >> y;
        if (t == 1) {
            cin >> k;
            add(x, y, k);
        } else {
            cout << getSum(x, y) << '\n';
        }
    }
    return 0;
}