#include <bits/stdc++.h>
using namespace std;
/*
我有个想法，使用线段树维护sum(bl...br)
单调栈维护min(al...ar)
单调维护递增
栈里的代表 [li, ri]的最小值
遇到一个比他小的，就把大的弹出，弹出顺带计算
把当前值的区间宽度增加
结束时栈不为空，则把最后一个弹出
计算后增加宽度
直到栈内为空

处理出最大连续子段和，最小连续子段和
 */
const int MAXN = 3 * 1e6 + 5;
struct Segtree {
    long long brr[MAXN];
    struct NODE {
        long long l, r, sum, lmax, rmax, maxdat, mindat, lmin, rmin;
    } t[MAXN << 2];
    void push_up(int p) {
        t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
        t[p].lmax = max(t[p << 1].lmax, t[p << 1].sum + t[p << 1 | 1].lmax);
        t[p].rmax = max(t[p << 1 | 1].rmax, t[p << 1 | 1].sum + t[p << 1].rmax);
        t[p].maxdat = max(max(t[p << 1].maxdat, t[p << 1 + 1].maxdat),
                          t[p << 1].rmax + t[p << 1 | 1].lmax);
        t[p].lmin = min(t[p << 1].lmin, t[p << 1].sum + t[p << 1 | 1].lmin);
        t[p].rmin = min(t[p << 1 | 1].rmin, t[p << 1 | 1].sum + t[p << 1].rmin);
        t[p].mindat = min(mi.mindat, t[p << 1 + 1].mindat),
                          t[p << 1].rmin + t[p << 1 | 1].lmin);
    }
    void build(int root, int l, int r) {
        t[root].l = l, t[root].r = r;
        if (l == r) {
            t[root].sum = t[p].lmax = t[p].rmax = t[p].lmin = t[p].rmin =
                t[p].maxdat = t[p].mindat = brr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
        push_up(root);
    }
    node query_maxs(int root, int l, int r){
        
    }
} tree;
long long arr[MAXN];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &tree.brr[i]);
    }
    tree.build(1, 1, n);
    stack<pair<long long, int>> stk;
    int w = 0;
    long long re = 0;
    for (int i = 1; i <= n; i++) {
        if (stk.empty()) {
            stk.push(make_pair(arr[i], 1));
        } else if (arr[i] > stk.top().first) {
            stk.push(make_pair(arr[i], 1));
        } else {
            while(stk.top().first > arr[i]){
                w += stk.top().second;
                re = max(re, stk.top().first)
            }
        }
    }
    return 0;
}
