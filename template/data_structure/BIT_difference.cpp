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

int n, m;

struct BIT {
    int bit[N], mi[N], ma[N];

    void add(int x, int v) {
        bit[x] = v;
        for (; x <= n; x += x & -x) {
            mi[x] = ma[x] = v;
            for (int i = 1; i < (x & -x); i <<= 1)
                mi[x] = min(mi[x], mi[x - i]),
                        ma[x] = max(ma[x], ma[x - i]);
        }
    }

    int difference(int l, int r) {
        int L = bit[r], R = bit[r];
        while (l <= r) {
            L = min(L, bit[r]);
            R = max(R, bit[r]);
            for (--r; r - l >= (r & -r); r -= (r & -r))
                L = min(L, mi[r]),
                        R = max(R, ma[r]);
        }
        return R - L + 1;
    }
};

BIT a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a.add(i, x);
    }
    while (m--) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) a.add(l, r);
        else cout << (a.difference(l, r) == r - l + 1 ? "YES" : "NO") << '\n';
    }
    return 0;
}