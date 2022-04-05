#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
constexpr int N = 1100000;
const db PI = acos(-1.0);
const db eps = 0.5;

struct comp {
    db a, b;
    comp(db _a = 0, db _b = 0) { a = _a, b = _b; }
    comp operator+(const comp&T) const { return comp(a + T.a, b + T.b); }
    comp operator-(const comp&T) const { return comp(a - T.a, b - T.b); }
    comp operator*(const comp&T) const { return comp(a * T.a - b * T.b, a * T.b + b * T.a); }
    comp operator/(const db&x) const { return comp(a / x, b / x); }
} a[N], b[N], c[N];

int A[N], B[N];
int limit = 1, pos[N], len;
int n, m;

void FFT(comp *a, int type) {
    for (int i = 0; i < limit; i++) if (i < pos[i]) swap(a[i], a[pos[i]]);
    for (int m = 1; m < limit; m <<= 1) {
        comp wn(cos(PI / m), sin(PI / m) * type);
        for (int i = 0, m2 = m << 1; i < limit; i += m2) {
            comp w(1, 0);
            for (int j = 0; j < m; j++, w = w * wn) {
                comp x = a[i + j];
                comp y = w * a[i + j + m];
                a[i + j] = x + y;
                a[i + j + m] = x - y;
            }
        }
    }
    if (type == -1) for (int i = 0; i < limit; i++) a[i] = a[i] / limit;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);
    int m, n;
    cin >> m >> n;
    string s, t;
    cin >> s >> t;
    reverse(s.begin(), s.end());
    for (int i = 0; i < m; i++) if (s[i] != '*') A[i] = s[i] - 'a' + 1;
    for (int i = 0; i < n; i++) if (t[i] != '*') B[i] = t[i] - 'a' + 1;
    while (limit <= n + m - 2) limit <<= 1, len++;
    for (int i = 0; i < limit; i++) pos[i] = pos[i >> 1] >> 1 | ((i & 1) << (len - 1));
    for (int i = 0; i < limit; i++) a[i] = comp(A[i] * A[i] * A[i], 0), b[i] = comp(B[i], 0);
    FFT(a, 1), FFT(b, 1);
    for (int i = 0; i < limit; i++) c[i] = c[i] + a[i] * b[i];
    for (int i = 0; i < limit; i++) a[i] = comp(A[i], 0), b[i] = comp(B[i] * B[i] * B[i], 0);
    FFT(a, 1), FFT(b, 1);
    for (int i = 0; i < limit; i++) c[i] = c[i] + a[i] * b[i];
    for (int i = 0; i < limit; i++) a[i] = comp(A[i] * A[i], 0), b[i] = comp(B[i] * B[i], 0);
    FFT(a, 1), FFT(b, 1);
    for (int i = 0; i < limit; i++) c[i] = c[i] - a[i] * b[i] * comp(2, 0);
    FFT(c, -1);
    vector<int> ans;
    for (int i = m - 1; i < n; i++) if (fabs(c[i].a) <= eps) ans.push_back(i - m + 2);
    cout << int(ans.size()) << '\n';
    for (int i = 0; i < int(ans.size()); i++) cout << ans[i] << " \n"[i == ans.size() - 1];
    return 0;
}