#include <bits/stdc++.h>
using namespace std;
using LL = long long;
struct Suffix_Array : vector<int> {
    vector<int> rank, lcp;
    vector<vector<int>> rmq;
    vector<int> log;
    Suffix_Array(const string& s) : vector<int>(s.size()), rank(s.size()), lcp(s.size()){
        int n = s.size(), k = 128;
        vector<int> cnt(max(n, k), 0), p(n);
        for (int i = 0; i < n; i += 1) cnt[rank[i] = s[i]] += 1;
        for (int i = 1; i < k; i += 1) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i -= 1) at(cnt[rank[i]] -= 1) = i;
        for (int h = 1; h <= n; h <<= 1) {
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i += 1) cnt[rank[i]] += 1;
            for (int i = 1; i < k; i += 1) cnt[i] += cnt[i - 1];
            k = 0;
            for (int i = n - h; i < n; i += 1) p[k ++] = i;
            for (int i = 0; i < n; i += 1) if (at(i) >= h) p[k ++] = at(i) - h;
            for (int i = n - 1; i >= 0; i -= 1) at(cnt[rank[p[i]]] -= 1) = p[i];
            p.swap(rank);
            rank[at(0)] = 0;
            k = 1;
            for (int i = 1; i < n; i += 1) {
                if (p[at(i)] != p[at(i - 1)] or at(i - 1) + h >= n or p[at(i) + h] != p[at(i - 1) + h]) k += 1;
                rank[at(i)] = k - 1;
            }
            if (k == n) break;
        }
        for (int i = 0, k = 0; i < n; i += 1) {
            if (k) k -= 1;
            if (rank[i]) while (s[i + k] == s[at(rank[i] - 1) + k]) k += 1;
            lcp[rank[i]] = k;
        }
        log.resize(n + 1);
        for (int i = 2; i <= n; i += 1) log[i] = log[i >> 1] + 1;
        rmq.resize(log.back() + 1, vector<int>(n));
        for (int i = 0; i <= log.back(); i += 1)
            for (int j = 0; j + (1 << i) - 1 < n; j += 1) {
                if (i == 0) rmq[i][j] = lcp[j];
                else rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
            }
    }
    int get_lcp(int i, int j) {
        i = rank[i];
        j = rank[j];
        if (i > j) std::swap(i, j);
        i += 1;
        int L = log[j - i + 1];
        return min(rmq[L][i], rmq[L][j - (1 << L) + 1]);
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    for (cin >> T; T; T -= 1) {
        string s, pre;
        cin >> s;
        for (char c = 'a'; c <= 'z'; c += 1) {
            int p = 0;
            while (p < s.size() and s[p] == c) p += 1;
            pre += s.substr(0, p);
            s = s.substr(p);
            if (ranges::count(s, c)) break;
        }
        if (s.empty()) {
            cout << pre << s << "\n";
            continue;
        }
        int ch = 0;
        string t = s;
        int n = s.size();
        ranges::reverse(t);
        t = s + t;
        Suffix_Array sa(t);
        auto cmp = [&](const vector<pair<int, int>>& p1, const vector<pair<int, int>>& p2) {
            int x = sa.get_lcp(p1[0].first, p2[0].first);
            int L1 = p1[0].second - p1[0].first + 1;
            int L2 = p2[0].second - p2[0].first + 1;
            if (x < L2)
                return t[p1[0].first + x] < t[p2[0].first + x];
            x = sa.get_lcp(p1[0].first + L2, p2[1].first);
            if (L2 + x < L1)
                return t[p1[0].first + L2 + x] < t[p2[1].first + x];
            if (p1[1].first > p1[1].second) return false;
            x = sa.get_lcp(p1[1].first, p2[1].first + L1 - L2);
            if (L1 + x < n)
                return t[p1[1].first + x] < t[p2[1].first + L1 - L2 + x];
            return false;
        };
        for (int i = 1; i < n; i += 1)
            if (cmp({{2 * n - 1 - i, 2 * n - 1}, {i + 1, n - 1}}, {{2 * n - 1 - ch, 2 * n - 1}, {ch + 1, n - 1}}))
                ch = i;
        reverse(s.begin(), s.begin() + ch + 1);
        cout << pre << s << "\n";
    }
    return 0;
}