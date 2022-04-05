#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair

using namespace std;
using ll = long long;
using pii = pair<int, int>;

constexpr double eps = 1e-8;
constexpr int NINF = 0xc0c0c0c0;
constexpr int INF = 0x3f3f3f3f;
constexpr ll mod = 1e9 + 7;
constexpr ll N = 2e5 + 5;

int n, m, M, zkw_mx[N << 2], zkw_cnt[N << 2];

inline void update(int x) {
    int ls = x << 1;
    int rs = ls | 1;
    if (zkw_mx[ls] == zkw_mx[rs]) {
        zkw_mx[x] = zkw_mx[ls];
        zkw_cnt[x] = zkw_cnt[ls] + zkw_cnt[rs];
    } else if (zkw_mx[ls] < zkw_mx[rs]) {
        zkw_mx[x] = zkw_mx[rs];
        zkw_cnt[x] = zkw_cnt[rs];
    } else {
        zkw_mx[x] = zkw_mx[ls];
        zkw_cnt[x] = zkw_cnt[ls];
    }
}

inline void update(int x, int val) {
    zkw_mx[x += M] = val;
    for (x >>= 1; x; x >>= 1) update(x);
}

inline void query(int l, int r) {
    int x, mx = -1, cnt = 0;
    for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        if (~l & 1) {
            x = l ^ 1;
            if (mx < zkw_mx[x]) {
                mx = zkw_mx[x];
                cnt = zkw_cnt[x];
            } else if (mx == zkw_mx[x]) cnt += zkw_cnt[x];
        }
        if (r & 1) {
            x = r ^ 1;
            if (mx < zkw_mx[x]) {
                mx = zkw_mx[x];
                cnt = zkw_cnt[x];
            } else if (mx == zkw_mx[x]) cnt += zkw_cnt[x];
        }
    }
    cout << mx << ' ' << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (M = 1; M <= n; M <<= 1);
    for (int i = 1; i <= n; i++) {
        cin >> zkw_mx[M + i];
        zkw_cnt[M + i] = 1;
    }
    for (int i = M - 1; i; i--) update(i);
    while (m--) {
        string op;
        int x, y;
        cin >> op >> x >> y;
        if (op == "Ask") query(x, y);
        else update(x, y);
    }
    return 0;
}