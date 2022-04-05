struct Trie {
    static constexpr int N = 4e6 + 5;
    int next[N][26], exist[N], cnt;

    void init() {
        for (int i = 0; i <= cnt; i++) {
            memset(next[i], 0, sizeof(next[i]));
            exist[i] = 0;
        }
        cnt = 0;
    }

    int id(char c) {
        return c - 'a';
    }

    void insert(const string &s, int v) {
        int cur = 0;
        for (auto c : s) {
            if (!next[cur][id(c)]) {
                next[cur][id(c)] = ++cnt;
            }
            cur = next[cur][id(c)];
        }
        exist[cur] = v;
    }

    int find_all(const string &s) {
        int cur = 0;
        for (auto c : s) {
            if (!next[cur][id(c)]) {
                return false;
            }
            cur = next[cur][id(c)];
        }
        return exist[cur];
    }
} trie;