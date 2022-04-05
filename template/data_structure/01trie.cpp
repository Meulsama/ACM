/*
    Don't forget to init()!
*/
struct Trie {
    const static int range = 2;
    const static int N = 32 * 100005;
    struct node {
        int next[range];
        int id;
    } Trie[N];

    int size;

    void init() {
        memset(Trie[0].next, 0, sizeof(Trie[0].next));
        Trie[0].id = 0;
        size = 1;
    }

    void insert(int x, int ID) {
        int cur = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (!Trie[cur].next[bit]) {
                memset(Trie[size].next, 0, sizeof(Trie[size].next));
                Trie[size].id = ID;
                Trie[cur].next[bit] = size++;
            }
            cur = Trie[cur].next[bit];
            Trie[cur].id = max(Trie[cur].id, ID);
        }
    }

    int query(int x, int y) {
        int cur = 0, ans = 0, i;
        for (i = 30; i >= 0; i--) {
            int u = (x >> i) & 1;
            int v = (y >> i) & 1;
            int w = u ^ v;
            if (!v && Trie[cur].next[u ^ 1]) ans = max(ans, Trie[Trie[cur].next[u ^ 1]].id);
            if (Trie[cur].next[w]) cur = Trie[cur].next[w];
            else break;
        }
        if (i == -1) ans = max(ans, Trie[cur].id);
        return ans;
    }
} trie;