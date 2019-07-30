#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL inf = 0x7ffffffffffffff;
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

处理出最大连续子段和，最小连续子段和(这个是错的，因为区间最大连续子段和，最小连续子段和可能是错的，可能不包含端点)
 */
const LL MAXN = 3 * 1e6 + 5;
LL arr[MAXN], brr[MAXN], sum[MAXN];
struct Segtree {
    struct NODE {
        int l, r;
        LL maxs, mins, dat;
    } tree[MAXN << 1];
    void push_up(int root) {
        tree[root].maxs = max(tree[root << 1].maxs, tree[root << 1 | 1].maxs);
        tree[root].mins = min(tree[root << 1].mins, tree[root << 1 | 1].mins);
        return;
    }
    void build(int root, int l, int r) {
        tree[root].l = l, tree[root].r = r;
        if (l == r) {
            tree[root].dat = tree[root].maxs = tree[root].mins = sum[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
        push_up(root);
    }
    long long query_maxs(int root, int l, int r) {
        if (l == tree[root].l && r == tree[root].r) {
            return tree[root].maxs;
        }
        int mid = (tree[root].l + tree[root].r) >> 1;
        if (l > tree[root].r) {
            return query_maxs(root << 1 | 1, l, r);
        } else if (r <= tree[root].l) {
            return query_maxs(root << 1, l, r);
        } else {
            return max(query_maxs(root << 1, l, mid),
                       query_maxs(root << 1 | 1, mid + 1, r));
        }
    }
    long long query_mins(int root, int l, int r) {
        if (l == tree[root].l && r == tree[root].r) {
            return tree[root].mins;
        }
        int mid = (tree[root].l + tree[root].r) >> 1;
        if (l > tree[root].r) {
            return query_mins(root << 1 | 1, l, r);
        } else if (r <= tree[root].l) {
            return query_mins(root << 1, l, r);
        } else {
            return min(query_mins(root << 1, l, mid),
                       query_mins(root << 1 | 1, mid + 1, r));
        }
    }
} seg;
int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> brr[i];
        sum[i] = sum[i - 1] + brr[i];
    }
    seg.build(1, 1, n);
    /*
    区间最小值， 区间最大值
    那么可以这样考虑
    

    进队不维护，出队维护

    维护的是单调递增
    


    出队的时候
    在栈中的含义是当前区间的最小值

    [l, mid][mid + 1, r]
    arr[mid] * (sum[mid] - query_mins(1, l, mid - 1))
    arr[mid] * (query_maxs(1, mid + 1, n) - query_min(1, l, mid - 1))

    arr[mid] * (sum[mid] - query_maxs(1, l, mid - 1))
    arr[mid] * (query_mins(1, mid + 1, n) - query_maxs(1, l, mid - 1))
     */
    stack<int> stk;
    long long re = -inf;
    for (int i = 1; i <= n; i++) {
        if (stk.empty()) {
            stk.push(i);
        } else {
            while (!stk.empty() && arr[stk.top()] > arr[i]) {
                int mid = stk.top();
                stk.pop();
                int l, r;
                if (stk.empty()) {
                    l = 1;
                } else {
                    l = stk.top() + 1;
                }
                r = i - 1;
                //cout << "l = " << l << " mid = " << mid << " r = " << r << endl;
                if (arr[stk.top()] > 0) {
                    re = max(re, arr[mid] * (sum[mid] -
                                             seg.query_mins(1, l, mid - 1)));
                    re = max(re, arr[mid] * (seg.query_maxs(1, mid + 1, r) -
                                             seg.query_mins(1, l, mid - 1)));
                } else {
                    re = max(re, arr[mid] * (sum[mid] -
                                             seg.query_maxs(1, l, mid - 1)));
                    re = max(re, arr[mid] * (seg.query_mins(1, mid + 1, r) -
                                             seg.query_maxs(1, l, mid - 1)));
                }
            }
            stk.push(i);
        }
    }
    int l, r, mid;
    r = n;
    while (!stk.empty()) {
        int mid = stk.top();
        stk.pop();
        if (stk.empty()) {
            l = 1;
        } else {
            l = stk.top() + 1;
        }
        if (arr[stk.top()] > 0) {
            re = max(re, arr[mid] * (sum[mid] - seg.query_mins(1, l, mid - 1)));
            re = max(re, arr[mid] * (seg.query_maxs(1, mid + 1, r) -
                                     seg.query_mins(1, l, mid - 1)));
        } else {
            re = max(re, arr[mid] * (sum[mid] - seg.query_maxs(1, l, mid - 1)));
            re = max(re, arr[mid] * (seg.query_mins(1, mid + 1, r) -
                                     seg.query_maxs(1, l, mid - 1)));
        }
    }
    cout << re << endl;
    return 0;
}