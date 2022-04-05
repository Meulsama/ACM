namespace Poly
{
    const int MAX_LEN = (1 << 19) + 5;
    const double PI = acos(-1.0);
 
    struct com
    {
        double a, b;
        com(double _a = 0.0, double _b = 0.0): a(_a), b(_b) { }
        com operator + (const com &t) const { return com(a + t.a, b + t.b); }
        com operator - (const com &t) const { return com(a - t.a, b - t.b); }
        com operator * (const com &t) const { return com(a * t.a - b * t.b, a * t.b + b * t.a); }
    };
 
    int len, cnt, rev[MAX_LEN];
    com g[MAX_LEN];
 
    inline void init(int N)
    {
        for (cnt = -1, len = 1; len <= N; len <<= 1) ++cnt;
        for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << cnt);
        g[0] = com(1.0, 0.0);
        for (int i = 1; i <= len; i++) g[i] = com(cos(PI * 2 / len * i), sin(PI * 2 / len * i));
    }
 
    inline void dft(com *x, int op = 1)
    {
        for (int i = 0; i < len; i++) if (i < rev[i]) swap(x[i], x[rev[i]]);
        for (int k = 2; k <= len; k <<= 1)
            for (int j = 0; j < len; j += k)
                for (int i = 0; i < k / 2; i++)
                {
                    com X = x[j + i], Y = x[j + i + k / 2] * g[len / k * (~op ? i : k - i)];
                    x[j + i] = X + Y, x[j + i + k / 2] = X - Y;
                }
        if (op == -1) { for (int i = 0; i < len; i++) x[i].a /= len, x[i].b /= len; }
    }
 
    inline void Mul(int *A, int n, int *B, int m, ll *C)
    {
        if (n + m == 0) { C[0] = (ll) A[0] * B[0]; return; }
        init(n + m);
        static com F[MAX_LEN], G[MAX_LEN], S[MAX_LEN];
        for (int i = 0; i < len; i++) F[i] = com(i <= n ? A[i] : 0.0, 0.0);
        for (int i = 0; i < len; i++) G[i] = com(i <= m ? B[i] : 0.0, 0.0);
        dft(F), dft(G);
        for (int i = 0; i < len; i++) S[i] = F[i] * G[i];
        dft(S, -1);
        for (int i = 0; i <= n + m; i++) C[i] = round(S[i].a);
    }
}