/*
    Don't forget to close:
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
*/

inline __int128 read() {
    __int128 x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}

inline void print(__int128 x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

template<typename T> inline void read(T &x) {
    x = 0;
    T f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) {x = x * 10 + ch - '0'; ch = getchar(); }
    x *= f;
}

template<typename T> inline void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}