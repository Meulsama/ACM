#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T, class F = std::plus<T>>
struct SegmentTree {
    #define ls (p << 1)
    #define rs (ls | 1)
    #define tm ((tl + tr) >> 1)

    const int n;
    const F merge;
    vector<T> t;

    SegmentTree(int n) : n(n), merge(F()), t(n << 2){}
    SegmentTree(const vector<T>& init) : SegmentTree(init.size()) {
        function<void(int, int, int)> build = [&](int p, int tl, int tr) {
            if (tr - tl == 1) {
                t[p] = init[tl];
                return;
            }
            build(ls, tl, tm);
            build(rs, tm, tr);
            up(p);
        };
        build(1, 0, n);
    }

    void up(int p) {
        t[p] = merge(t[ls], t[rs]);
    }

    void modify(int p, int tl, int tr, int k, const T& v) {
        if (tr - tl == 1) {
            t[p] = v;
            return;
        }
        if (k < tm) modify(ls, tl, tm, k, v);
        else modify(rs, tm, tr, k, v);
        up(p);
    }

    void modify(int k, const T& v) {
        modify(1, 0, n, k, v);
    }

    T rangeQuery(int p, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return T();
        if (l <= tl && tr <= r) return t[p];
        return merge(rangeQuery(ls, tl, tm, l, r), rangeQuery(rs, tm, tr, l, r));
    }

    T rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(20);
    
    return 0;
}