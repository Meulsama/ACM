#define ls (p << 1)
#define rs (ls | 1)
#define tm ((tl + tr) >> 1)

int mi[N << 2], a[N << 2];

void up(int p) {
    mi[p] = min(mx[ls], mx[rs]);
}

void build(int p, int tl, int tr) {
    if (tl == tr) {
        mi[p] = a[tl];
    } else {
        build(ls, tl, tm);
        build(rs, tm + 1, tr);
        up(p);
    }
}

void modify(int p, int tl, int tr, int pos, int v) {
    if (tl == tr) {
        mi[p] = v;
    } else {
        if (tm >= pos) modify(ls, tl, tm, pos, v);
        else modify(rs, tm + 1, tr, pos, v);
        up(p);
    }
}

int query(int p, int tl, int tr, int l, int r) {
    if (l <= tl && tr <= r) {
        return mi[p];
    } else {
        int ans = INT_MAX;
        if (tm >= l) ans = min(ans, query(ls, tl, tm, l, r));
        if (tm < r) ans = min(ans, query(rs, tm + 1, tr, l, r));
        return ans;
    }
}