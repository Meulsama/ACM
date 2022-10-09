struct SegmentTree {
#define mid ((l + r) >> 1)
#define ls (p + 1)
#define rs (p + ((mid - l + 1) << 1))

  struct node {
    int add = 0;
    int mn = 0;

    void apply(int l, int r, int v) {
      add += v;
      mn += v;
    }
  };

  node unite(const node &a, const node &b) const {
    node res;
    res.mn = min(a.mn, b.mn);
    return res;
  }

  inline void push(int p, int l, int r) {
    if (tree[p].add != 0) {
      tree[ls].apply(l, mid, tree[p].add);
      tree[rs].apply(mid + 1, r, tree[p].add);
      tree[p].add = 0;
    }
  }

  inline void pull(int p, int rs_) { tree[p] = unite(tree[ls], tree[rs_]); }

  int n;
  vector<node> tree;

  SegmentTree(int _n) : n(_n) {
    assert(n > 0);
    tree.resize(2 * n - 1);
    build(0, 0, n - 1);
  }

  template <typename T>
  SegmentTree(const vector<T> &v) {
    n = v.size();
    assert(n > 0);
    tree.resize(2 * n - 1);
    build(0, 0, n - 1, v);
  }

  void build(int p, int l, int r) {
    if (l == r) {
      return;
    }
    build(ls, l, mid);
    build(rs, mid + 1, r);
    pull(p, rs);
  }

  template <typename T>
  void build(int p, int l, int r, const vector<T> &v) {
    if (l == r) {
      tree[p].apply(l, r, v[l]);
      return;
    }
    build(ls, l, mid, v);
    build(rs, mid + 1, r, v);
    pull(p, rs);
  }

  node get(int p, int l, int r, int ll, int rr) {
    if (ll <= l && r <= rr) {
      return tree[p];
    }
    node res;
    push(p, l, r);
    if (rr <= mid) {
      res = get(ls, l, mid, ll, rr);
    } else if (ll > mid) {
      res = get(rs, mid + 1, r, ll, rr);
    } else {
      res = unite(get(ls, l, mid, ll, rr), get(rs, mid + 1, r, ll, rr));
    }
    pull(p, rs);
    return res;
  }

  template <typename... T>
  void modify(int p, int l, int r, int ll, int rr, const T &...v) {
    if (ll <= l && r <= rr) {
      tree[p].apply(l, r, v...);
      return;
    }
    push(p, l, r);
    if (ll <= mid) {
      modify(ls, l, mid, ll, rr, v...);
    }
    if (rr > mid) {
      modify(rs, mid + 1, r, ll, rr, v...);
    }
    pull(p, rs);
  }

  int find_first_knowingly(int p, int l, int r,
                           const function<bool(const node &)> &f) {
    if (l == r) {
      return l;
    }
    push(p, l, r);
    int res;
    if (f(tree[ls])) {
      res = find_first_knowingly(ls, l, mid, f);
    } else {
      res = find_first_knowingly(rs, mid + 1, r, f);
    }
    pull(p, rs);
    return res;
  }

  int find_first(int p, int l, int r, int ll, int rr,
                 const function<bool(const node &)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(tree[p])) {
        return -1;
      }
      return find_first_knowingly(p, l, r, f);
    }
    push(p, l, r);
    int res = -1;
    if (ll <= mid) {
      res = find_first(ls, l, mid, ll, rr, f);
    }
    if (rr > mid && res == -1) {
      res = find_first(rs, mid + 1, r, ll, rr, f);
    }
    pull(p, rs);
    return res;
  }

  int find_last_knowingly(int p, int l, int r,
                          const function<bool(const node &)> &f) {
    if (l == r) {
      return l;
    }
    push(p, l, r);
    int res;
    if (f(tree[rs])) {
      res = find_last_knowingly(rs, mid + 1, r, f);
    } else {
      res = find_last_knowingly(ls, l, mid, f);
    }
    pull(p, rs);
    return res;
  }

  int find_last(int p, int l, int r, int ll, int rr,
                const function<bool(const node &)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(tree[p])) {
        return -1;
      }
      return find_last_knowingly(p, l, r, f);
    }
    push(p, l, r);
    int res = -1;
    if (rr > mid) {
      res = find_last(rs, mid + 1, r, ll, rr, f);
    }
    if (ll <= mid && res == -1) {
      res = find_last(ls, l, mid, ll, rr, f);
    }
    pull(p, rs);
    return res;
  }

  node get(int x) {
    assert(0 <= x && x <= n - 1);
    return get(0, 0, n - 1, x, x);
  }

  node get(int ll, int rr) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(0, 0, n - 1, ll, rr);
  }

  template <typename... T>
  void modify(int ll, int rr, const T &...v) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return modify(0, 0, n - 1, ll, rr, v...);
  }

  int find_first(int ll, int rr, const function<bool(const node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return find_first(0, 0, n - 1, ll, rr, f);
  }

  int find_last(int ll, int rr, const function<bool(const node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return find_last(0, 0, n - 1, ll, rr, f);
  }
};