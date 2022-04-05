using db = double;
const db PI = acos(-1);
constexpr db EPS = 1e-9;

int sign(db a) { return a < -EPS ? -1 : a > EPS; }

int cmp(db a, db b) { return sign(a - b); }

struct P {
    db x, y;
    P() {}
    P(db _x, db _y) : x(_x), y(_y){}
    P operator+(P p) { return {x + p.x, y + p.y}; }
    P operator-(P p) { return {x - p.x, y - p.y}; }
    P operator*(db d) { return {x * d, y * d}; }
    P operator/(db d) { return {x / d, y / d}; }

    // like pair<int, int> to cmp
    // bool operator<(P p) const {
    //     int c = cmp(x, p.x);
    //     if (c) return c == -1;
    //     return cmp(y, p.y) == -1;
    // }

    //Psort
    bool operator<(P p) const {
        return upper() == p.upper() ? sign(det(p)) == -1 : upper() < p.upper();
    }

    bool operator==(P p) const {
        return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;
    }

    db dot(P p) const { return x * p.x + y * p.y; }
    db det(P p) const { return x * p.y - y * p.x; }

    db abs2() { return x * x + y * y; }
    db abs() { return sqrt(abs2()); }
    db alpha() { return atan2(y, x); }
    db distTo(P p) { return (*this - p).abs(); }
    P rot90() { return {-y, x}; }
    P irot90() { return {y, -x}; }
    P rot(db angle) { return { x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle)}; }
    P unit() { return *this / abs(); }
    bool upper() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }

    void read() { cin >> x >> y;}
    void write() const { cerr << "(" << x << ", " << y << ")\n"; }
};

// struct L {
//     P ps[2];
//     P
    
// };

void Psort(vector<P> &Ps, P c = {0, 0}) {
    sort(Ps.begin(), Ps.end(), [&](P a, P b) {
        return (a - c).upper() == (b - c).upper() ? sign((a - c).det((b - c))) == -1 : (a - c).upper() < (b - c).upper();
    });
}

db area(vector<P> Ps) {
    db sum = 0;
    for (int i = 0; i < Ps.size(); i++) sum += (Ps[i].det(Ps[(i + 1) % Ps.size()]));
    return sum / 2;
}

#define cross(p1,p2,p3) ((p2.x-p1.x)*(p3.y-p1.y)-(p3.x-p1.x)*(p2.y-p1.y))
#define crossOp(p1,p2,p3) sign(cross(p1,p2,p3))

//判断两直线是否存在交点
bool chkLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return sign(a1 + a2) != 0;
}

P isLL(P p1, P p2, P q1, P q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

P isLL(L l1,L l2){ return isLL(l1[0], l1[1], l2[0], l2[1]); }
