struct HashString {
    static constexpr unsigned int base = 137;
    int n;
    vector<unsigned int> H, P;
    HashString() {}
    HashString(string s) : n(int(s.size())), H((int)s.size() + 1, 0), P((int)s.size() + 1, 0) {
        P[0] = 1;
        s = " " + s;
        for (int i = 1; i <= n; i++) {
            H[i] = H[i - 1] * base + s[i] - 'a' + 1;
            P[i] = P[i - 1] * base;
        }
    }

    unsigned int get(int L, int R) {
        return H[R] - H[L - 1] * P[R - L + 1];
    }
};