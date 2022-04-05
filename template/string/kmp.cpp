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

string s, t;
int n, m, kmp[N], nx[N];

void get_nextval() {
    int i = 0, j = -1, len2 = t.size();
    kmp[0] = -1;
    while (i < len2) {
        if (j == -1 || t[i] == t[j]) {
            ++i, ++j;
            if (t[i] != t[j]) kmp[i] = j;
            else kmp[i] = kmp[j];
        } else j = kmp[j];
    }
}

void get_next() {
    int i = 0, j = -1, len2 = t.size();
    nx[0] = -1;
    while (i < len2) {
        if (j == -1 || t[i] == t[j]) nx[++i] = ++j;
        else j = nx[j];
    }
}

void get_kmp() {
    int i = 0, j = 0, len1 = s.size(), len2 = t.size();
    while (i < len1) {
        if (j == -1 || s[i] == t[j]) i++, j++;
        else j = kmp[j];
        if (j == len2) cout << i - j + 1 << '\n', j = kmp[j];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s >> t;
    n = s.size(), m = t.size();
    get_nextval();
    get_kmp();
    get_next();
    for (int i = 1; i <= m; i++) cout << nx[i] << " \n"[i == m];
    return 0;
}