namespace HASH {
    int to[N], cnt[N], next[N], head[mod], tot;

    inline void clear() { 
        memset(head, tot = 0, sizeof(head));
        memset(cnt, 0, sizeof(cnt)); 
    }

    inline void insert(int x) {
        int k = x % mod;
        for (int i = head[k]; i; i = next[i])
            if (to[i] == x) {
                cnt[i]++;
                return;
            }
        to[++tot] = x;
        cnt[tot] = 1;
        next[tot] = head[k];
        head[k] = tot;
    }

    inline int query(int x) {
        int k = x % mod;
        for (int i = head[k]; i; i = next[i]) if (to[i] == x) return cnt[i];
        return 0;
    }
}

template<typename T> struct Hash {
    int n, p, N;
    vector<vector<T>> G;
    vector<T> cnt, value;

    Hash(int N, int p) : n(0), p(p), G(p), cnt(N), value(N) {}

    void clear() {
        n = 0;
        vector<vector<T>> X;
        swap(G, X);
        vector<T> x1, x2;
        swap(cnt, x1);
        swap(value, x2);
    }

    void insert(int x) {
        int k = x % p;
        for (auto i : G[k]) {
            if (value[i] == x) {
                cnt[i]++;
                return;
            }
        }
        value[n] = x;
        cnt[n] = 1;
        G[k].push_back(n++);
    }

    int query(int x) {
        int k = x % p;
        for (auto i : G[k]) {
            if (value[i] == x) {
                return cnt[i];
            }
        }
        return 0;
    }
};