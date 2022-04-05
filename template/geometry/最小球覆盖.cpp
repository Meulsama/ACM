#include<cstdio>
#include<cmath>
#include<algorithm>

using namespace std;
const double eps = 1e-3;

int n;

struct Point {
    double x;
    double y;
    double z;

    Point(double _x = 0.0, double _y = 0.0, double _z = 0.0) {
        x = _x;
        y = _y;
        z = _z;
    }
};

Point points[105];

inline double dis(Point a, Point b) {
    double norm = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
    return sqrt(norm);
}

double solve() {
    double T = 1000.0; //初始温度
    double rate = 0.99999; //温度下降系数
    Point ans_p;    //初始圆心
    int cur;
    Point max_p; //距离圆心最远的点
    double ans = 1e99;
    while (T > eps) //模拟降温
    {
        double max_dis = 0.0; //选定圆心到最远点距离
        for (int i = 1; i <= n; ++i) { //最远的点即points[cur]
            if (dis(ans_p, points[i]) > max_dis) {
                max_dis = dis(ans_p, points[i]);
                cur = i;
            }
        }
        ans = min(ans, max_dis);
        ans_p.x += (points[cur].x - ans_p.x) * (T / 1000.0);
        ans_p.y += (points[cur].y - ans_p.y) * (T / 1000.0);
        ans_p.z += (points[cur].z - ans_p.z) * (T / 1000.0);
        T *= rate;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lf%lf%lf", &points[i].x, &points[i].y, &points[i].z);
    }
    printf("%.15f\n", solve());
    return 0;
}