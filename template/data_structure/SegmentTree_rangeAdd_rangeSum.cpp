template<typename T>
struct SegmentTree {
#define ls (p << 1)
#define rs (ls | 1)
#define tm ((tl + tr) >> 1)
    int n;
    vector<T> a, sum, tag;
    SegmentTree(int n) : n(n), sum(n << 2), tag(n << 2) {}
    SegmentTree(const vector<T> &a) : SegmentTree(a.size()) {
        function<void(int, int, int)> build = [&](int p, int tl, int tr) {
            if (tl == tr) {
                sum[p] = a[tl - 1];
                return;
            }
            build(ls, tl, tm);
            build(rs, tm + 1, tr);
            up(p);
        };
        build(1, 1, n);
    }

    void modify(int p, int tl, int tr, T v) {
        tag[p] += v;
        sum[p] += (tr - tl + 1) * v;
    }

    void down(int p, int tl, int tr) {
        modify(ls, tl, tm, tag[p]);
        modify(rs, tm + 1, tr, tag[p]);
        tag[p] = 0;
    }

    void up(int p) {
        sum[p] = sum[ls] + sum[rs];
    }

    void rangeAdd(int p, int tl, int tr, int l, int r, T v) {
        if (r < tl || tr < l) return;
        if (l <= tl && tr <= r) {
            modify(p, tl, tr, v);
            return;
        }
        down(p, tl, tr);
        rangeAdd(ls, tl, tm, l, r, v);
        rangeAdd(rs, tm + 1, tr, l, r, v);
        up(p);
    }

    T rangeSum(int p, int tl, int tr, int l, int r) {
        if (r < tl || tr < l) return 0;
        if (l <= tl && tr <= r) {
            return sum[p];
        }
        T res = 0;
        down(p, tl, tr);
        res += rangeSum(ls, tl, tm, l, r);
        res += rangeSum(rs, tm + 1, tr, l, r);
        return res;
    }
};