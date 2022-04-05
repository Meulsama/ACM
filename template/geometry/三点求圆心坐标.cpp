#include <iostream>
#include <iomanip>

#define fi first
#define se second
#define mp make_pair

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const double eps = 1e-8;
const int NINF = 0Xc0c0c0c0;
const int INF = 0X3f3f3f3f;
const ll mod = 1e9 + 7;
const ll N = 1e6 + 5;

using db = double;

pair<db, db> solve(db X1, db Y1, db X2, db Y2, db X3, db Y3) {
    double X = ((Y2 - Y1) * (Y3 * Y3 - Y1 * Y1 + X3 * X3 - X1 * X1) - (Y3 - Y1) * (Y2 * Y2 - Y1 * Y1 + X2 * X2 - X1 * X1)) / (2.0 * ((X3 - X1) * (Y2 - Y1) - (X2 - X1) * (Y3 - Y1)));
    double Y = ((X2 - X1) * (X3 * X3 - X1 * X1 + Y3 * Y3 - Y1 * Y1) - (X3 - X1) * (X2 * X2 - X1 * X1 + Y2 * Y2 - Y1 * Y1)) / (2.0 * ((Y3 - Y1) * (X2 - X1) - (Y2 - Y1) * (X3 - X1)));
    return make_pair(X, Y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    db X1, X2, X3, Y1, Y2, Y3;
    pair<db, db> P = solve(X1, Y1, X2, Y2, X3, Y3);
    cout << P.first << " " << P.second << '\n';
    return 0;
}