template <typename T>
struct hash_table {
    static const int N = 10000121;
    int head[N], nxt[N], tm[N], tmcnt = 1, tot = 0;
    ll key[N];
    T val[N];
    hash_table() {
        memset(tm, 0, sizeof(tm));
    }
    void clear() {
        tot = 0;
        tmcnt++;
    }
    bool count(ll k) {
        int x = k % N; if(x < 0) x += N;
        if(tm[x] != tmcnt) return 0;
        for(int i = head[x]; ~i; i = nxt[i]) {
            if(key[i] == k) return 1;
        }
        return 0;
    }
    T & operator [](ll k) {
        int x = k % N; if(x < 0) x += N;
        if(tm[x] != tmcnt) tm[x] = tmcnt, head[x] = -1;
        for(int i = head[x]; ~i; i = nxt[i]) {
            if(key[i] == k) return val[i];
        }
        nxt[tot] = head[x], head[x] = tot, key[tot] = k, val[tot] = T();
        return val[tot++];
    }
};