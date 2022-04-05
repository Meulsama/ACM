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

int n, A[N];

int Min_show() {
    int i = 0, j = 1, k = 0;
    while (i < n and j < n and k < n) {
        if (A[(i + k) % n] == A[(j + k) % n]) k++;
        else {
            A[(i + k) % n] > A[(j + k) % n] ? i += k + 1 : j + k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    return min(i, j);
}

int Max_show() {
    int i = 0, j = 1, k = 0;
    while (i < n and j < n and k < n) {
        if (A[(i + k) % n] == A[(j + k) % n]) k++;
        else {
            A[(i + k) % n] < A[(j + k) % n] ? i += k + 1 : j + k + 1;
            if (i == j) i++;
            k = 0;
        }
    }
    return min(i, j);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int s = Min_show();
    for (int i = 0; i < n; i++) cout << A[(s + i) % n] << " \n"[i == n - 1];
    return 0;
}