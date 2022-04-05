template<typename T>
struct Fenwick {
    int n;
    vector<T> a;

    Fenwick(int n) : n(n), a(n) {}
    
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }

    void rangeAdd(int l, int r, T v) {
        add(l, v);
        add(r + 1, -v);
    }

    T sum(int x) {
        T s = 0;
        for (int i = x + 1; i > 0; i -= i & -i) {
            s += a[i - 1];
        }
        return s;
    }

    T rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};