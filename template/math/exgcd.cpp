/*
    x_min
    x = (x % b + b) % b
*/
template<typename T>
T exgcd(T a, T b, T &x, T &y) {
    if (!b) { x = 1, y = 0; return a; }
    int d = exgcd(b, a % b, x, y);
    int z = x;
    x = y, y = z - y * (a / b);
    return d;
}

template<typename T>
T inv(T a, T p) {
    T x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}