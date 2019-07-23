#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
typedef long long ll;
int sgn(double x) {
    if (fabs(x) < eps) return 0;
    if (x < 0)
        return -1;
    else
        return 1;
}

struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
    Point operator-(const Point &b) const { return Point(x - b.x, y - b.y); }
    int operator^(const Point &b) const { return x * b.y - y * b.x; }
    int operator*(const Point &b) const { return x * b.x + y * b.y; }
    friend int dis2(Point a) { return a.x * a.x + a.y * a.y; }
    friend bool operator<(const Point &a, const Point &b) {
        if (fabs(a.y - b.y) < eps) return a.x < b.x;
        return a.y < b.y;
    }
};
typedef Point Vector;
double Dot(Point A, Point B) { return A.x * B.x + A.y * B.y; }      //点积
double Cross(Vector A, Vector B) { return A.x * B.y - A.y * B.x; }  //叉积
double Length(Vector A) { return sqrt(Dot(A, A)); }                 // OA长
double Angle(Point A, Point B) {
    return acos(Dot(A, B) / Length(A) / Length(B));
}  // OA和OB的夹角
//判断线段相交,不在端点相交
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1),
           c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
}

int graham(Point p[], int n, Point q[]) {
    int top = 1;
    sort(p, p + n);
    if (n == 0) return 0;
    q[0] = p[0];
    if (n == 1) return 1;
    q[1] = p[1];
    if (n == 2) return 2;
    q[2] = p[2];
    for (int i = 2; i < n; i++) {
        while (top && (Cross(q[top] - q[top - 1], p[i] - q[top - 1]) <= 0))
            top--;
        q[++top] = p[i];
    }
    int len = top;
    q[++top] = p[n - 2];
    for (int i = n - 3; i >= 0; i--) {
        while (top != len &&
               (Cross(q[top] - q[top - 1], p[i] - q[top - 1]) <= 0))
            top--;
        q[++top] = p[i];
    }
    return top;
}

bool C_S(Point *ch1, int t1, Point *ch2, int t2)  //判断凸包是否相交
{
    double angle[1010], x;
    int i, j, k, m;
    if (t1 == 1) return true;
    if (t1 == 2) {
        for (i = 0; i < t2; i++) {
            k = sgn(Cross(ch1[1] - ch1[0], ch2[i] - ch1[0]));
            if (k == 0 && Dot(ch1[1] - ch1[0], ch2[i] - ch1[0]) > 0) {
                if (Length(ch2[i] - ch1[0]) < Length(ch1[1] - ch1[0])) break;
            }
        }
        if (i < t2) return false;
        if (t2 == 2 &&
            SegmentProperIntersection(ch1[0], ch1[1], ch2[0], ch2[1]))
            return false;
        return true;
    }
    angle[0] = 0;
    for (i = 2; i < t1; i++)
        angle[i - 1] = Angle(ch1[1] - ch1[0], ch1[i] - ch1[0]);
    for (i = 0; i < t2; i++) {
        j = sgn(Cross(ch1[1] - ch1[0], ch2[i] - ch1[0]));
        if (j < 0 || (j == 0 && Dot(ch1[1] - ch1[0], ch2[i] - ch1[0]) < 0))
            continue;
        j = sgn(Cross(ch1[t1 - 1] - ch1[0], ch2[i] - ch1[0]));
        if (j > 0 || (j == 0 && Dot(ch1[t1 - 1] - ch1[0], ch2[i] - ch1[0]) < 0))
            continue;
        x = Angle(ch1[1] - ch1[0], ch2[i] - ch1[0]);
        m = lower_bound(angle, angle + t1 - 1, x) - angle;
        if (m == 0)
            j = 0;
        else
            j = m - 1;
        k = sgn(Cross(ch1[j + 1] - ch2[i], ch1[j + 2] - ch2[i]));
        if (k >= 0) break;
    }
    if (i < t2) return false;
    return true;
}

Point p1[300], p2[300], ch1[300], ch2[300];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        int cnt1 = 0, cnt2 = 0;
        for (int i = 0; i < n; i++) {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            if (c == 1) {
                p1[cnt1++] = Point(x, y);
            } else
                p2[cnt2++] = Point(x, y);
        }
        int t1 = graham(p1, cnt1, ch1);
        int t2 = graham(p2, cnt2, ch2);
        if (C_S(ch1, t1, ch2, t2) && C_S(ch2, t2, ch1, t1)) printf("Successful!\n");  
        else printf("Infinite loop!\n");
    }
}