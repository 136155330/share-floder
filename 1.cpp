#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
vector<int> vec;
int gets(int x) {
    return lower_bound(vec.begin(), vec.end(), x) - vec.begin() + 1;
}
struct Segment_forest {
    int root[MAXN];
    struct NODE {
        int l, r, sum;
    } segtree[MAXN * 20];
    int tot;
    int build(int l, int r)  /// return p p的值是点的坐标
    {
        int p = ++tot;
        segtree[p].sum = 0;
        if (l == r) {
            /**
             一层一层的返回就对了。。。。。。
             返回这个节点的坐标就对了。。。。。
             然后才能实现 l r 的指向
             **/
            return p;  ///返回指向
        }
        int mid = (l + r) >> 1;
        segtree[p].l = build(l, mid);
        segtree[p].r = build(mid + 1, r);
        return p;
    }
    int update(int now, int l, int r, int pos, int val)
    /**
     now - 当前节点 pos - 指要更新的点 val - 权值
     每次更新，都会创建一条链，所以得更新tot
     **/
    {
        int p = ++tot;
        segtree[p] = segtree[now];  ///这样会将上一个的点
        ///的值赋值给当前的点，这样不需要修改的那棵子树的连接
        ///这样每次多生成的一颗线段树，只要多一条链，所以节省了空间
        if (l == r) {
            segtree[p].sum += val;  ///如果每次更新到底的话，那么就更新底的值
            return p;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)  ///如果增加的点 < mid 那么肯定可以往左子树移动
        {
            segtree[p].l = update(segtree[p].l, l, mid, pos, val);
        } else  ///否则向右子树移动
        {
            segtree[p].r = update(segtree[p].r, mid + 1, r, pos, val);
        }
        segtree[p].sum = segtree[segtree[p].l].sum + segtree[segtree[p].r].sum;
        return p;
    }
    int query(int p, int q, int l, int r, int k) {
        if (l == r) return l;  ///查询到底就输出
        int mid = (l + r) >> 1;
        int cnt = segtree[segtree[p].l].sum - segtree[segtree[q].l].sum;
        ///将两棵树相减，可得要的状态
        if (k <= cnt)  /// k 即为第k小，那么就是查询第k小，判断个数再进行移动
        {
            return query(segtree[p].l, segtree[q].l, l, mid, k);
        } else {
            return query(segtree[p].r, segtree[q].r, mid + 1, r, k - cnt);
        }
    }
} tree;
int arr[MAXN];
int main() {
    int n, q;
    //freopen("C:/Users/user/Desktop/1011.in", "r", stdin);
    //freopen("C:/Users/user/Desktop/1011.myout", "w", stdout);
    while (~scanf("%d%d", &n, &q)) {
        vec.clear();
        tree.tot = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
            vec.push_back(arr[i]);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        tree.root[0] = tree.build(1, n);
        for(int i = 0; i < n; i ++){
            tree.root[i + 1] = tree.update(tree.root[i], 1, n, gets(arr[i]), 1);
        }
        for(int i = 0; i < q; i ++){
            int l, r;
            scanf("%d%d", &l, &r);
            vector<long long>re;
            re.clear();
            long long result = -1;
            for(int j = 0; j < min(47, r - l + 1); j ++){
                re.push_back(vec[tree.query(tree.root[r], tree.root[l - 1], 1, n, r - l + 1 - j) - 1]);
                if(re.size() >= 3){
                    if(re[j - 2] < re[j - 1] + re[j]){
                        result = re[j] + re[j - 1] + re[j - 2];
                        break;
                    }
                }
            }
            printf("%lld\n", result);
        }
    }
    return 0;
}