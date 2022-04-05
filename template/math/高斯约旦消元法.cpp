#include <bits/stdc++.h>

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ls (p << 1)
#define rs (ls | 1)
#define tm ((tl + tr) >> 1)
#define lowbit(x) ((x) & -(x))

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

constexpr double eps = 1e-8;
constexpr int NINF = 0xc0c0c0c0;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNINF = 0xc0c0c0c0c0c0c0c0;
constexpr ll LINF = 0x3f3f3f3f3f3f3f3f;
constexpr ll mod = 1e9 + 7;
constexpr ll N = 1e6 + 5;

int n;
double a[N][N];

void Gauss_Jordan() {
    for (int i = 1; i <= n; i++) {
        int mx = i;
        for (int j = i + 1; j <= n; j++) if (fabs(a[j][i]) > fabs(a[mx][i])) mx = j;
        if (i != mx) for (int j = 1; j <= n + 1; j++) swap(a[i][j], a[mx][j]);
        if (!a[i][i]) {
            cout << "No Solution\n";
            exit(0);
        }
        for (int j = 1; j <= n; j++) {
            if (j != i) {
                double tmp = a[j][i] / a[i][i];
                for (int k = i + 1; k <= n + 1; k++) a[j][k] -= a[i][k] * tmp;
            }
        }
    }
    for (int i = 1; i <= n; i++) a[i][n + 1] = a[i][n + 1] / a[i][i];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cin >> a[i][j];
        }
    }
    Gauss_Jordan();
    for (int i = 1; i <= n; i++)
        cout << fixed << setprecision(2) << a[i][n + 1] << '\n';
    return 0;
}