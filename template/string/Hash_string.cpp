/*
    Hash S(s);
    Sometimes we need to use a lot of primes to hash instead of overflow.

    if MLE, try: using ull = unisgned int;
*/
struct HashString{
    static constexpr ll mod1 = 1610612741;
    static constexpr ll mod2 = 998244353;
    static constexpr ll base = 379;
    static constexpr ll basei = 137;
    int n;
    vector<ll> Hi, Pi;
    vector<ll> H, P;
    HashString() {}
    HashString(string s) : n(int(s.size())), Hi((int)s.size() + 1, 0), Pi((int)s.size() + 1, 0), H((int)s.size() + 1, 0), P((int)s.size() + 1, 0) {
        P[0] = 1;
        Pi[0] = 1;
        s = " " + s;
        for (int i = 1; i <= n; i++) {
            H[i] = H[i - 1] * base % mod1 + s[i] - 'a' + 1;
            H[i] %= mod1;
            P[i] = P[i - 1] * base % mod1;
            Hi[i] = Hi[i - 1] * basei % mod2 + s[i] - 'a' + 1;
            Hi[i] %= mod2;
            Pi[i] = Pi[i - 1] * basei % mod2;
        }
    }

    pair<ll, ll> get(int L, int R) {
        return make_pair((H[R] - H[L - 1] * P[R - L + 1] % mod1 + mod1) % mod1, (Hi[R] - Hi[L - 1] * Pi[R - L + 1] % mod2 + mod2) % mod2);
    }
};

struct HASH {
    size_t operator()(const pair<int, int>&x)const {
        return hash<long long>()(((long long)x.first) ^ (((long long)x.second) << 32));
    }
};

unordered_set<pair<ll, ll>, pair_hash> S;