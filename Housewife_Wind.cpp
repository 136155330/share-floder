#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
int n, m, r;///n - 点的个数 m - 边数 
const int p = 0x7fffffff; 
struct EDGE{
    int tot;
    int head[MAXN];
    struct NODE{
        int u, v, next;
    }arr[MAXN << 1];
    void Init(){
        for(int i = 0; i <= n + 1; i ++){
            head[i] = -1;
        }
        tot = 0;
    }
    void add(int u, int v){
        arr[tot].u = u, arr[tot].v = v;
        arr[tot].next = head[u], head[u] = tot ++;
    }
}e;
int deep[MAXN], fa[MAXN], son[MAXN], size[MAXN], id[MAXN], top[MAXN], value[MAXN], tree_arr[MAXN];
int dfs1(int now, int f, int dep){///now - 当前的节点， f - 父亲节点， dep - 当前结点的深度
    cout << "now = " << now << "f = " << f << "dep = " << dep << endl;
    deep[now] = dep;///将深度赋值给当前的点
    fa[now] = f;///标记父亲节点是谁
    size[now] = 1;///标记子树的大小
    int maxson = -1;///来寻找子树最大的点（即重点）
    for(int i = e.head[now]; ~i; i = e.arr[i].next){
        int to = e.arr[i].v;
        if(to == f) {continue;}///双向边跑到father就跳过
        size[now] += dfs1(e.arr[i].v, now, dep + 1);///更新子树
        if(size[e.arr[i].v] > maxson){///判断重点
            maxson = size[e.arr[i].v];
            son[now] = e.arr[i].v;///改变重点
        }
    }
    return size[now];///返回子树的大小
}
int cnt = 0;
void dfs2(int now, int topf){
    id[now] = ++cnt;///给点新的编号
    tree_arr[cnt] = value[now];///给点赋值
    top[now] = topf;///重链的头节点
    if(!son[now]) return ;///如果没有重子点，那么证明这个点是叶子节点可以结束了
    dfs2(son[now], topf);///先跑重子节点
    for(int i = e.head[now]; ~i; i = e.arr[i].next){
        dfs2(e.arr[i].v, e.arr[i].v);///跑轻节点，那么轻节点的重链头节点是他自己
    }
}
struct Segtree{
    struct NODE{
        int l, r, lazy, sum, maxs, mins;
    }tree[MAXN << 2];
    inline void push_down(int root){
        if(tree[root].lazy){
            tree[root << 1].lazy = tree[root].lazy;
            tree[root << 1 | 1].lazy = tree[root].lazy;
            tree[root << 1].maxs += tree[root].lazy;
            tree[root << 1 | 1].maxs += tree[root].lazy;
            tree[root << 1].mins += tree[root].lazy;
            tree[root << 1 | 1].mins += tree[root].lazy;
            tree[root << 1].sum += (tree[root << 1].r - tree[root << 1].l + 1) * tree[root].lazy;
            tree[root << 1 | 1].sum += (tree[root << 1 | 1].r - tree[root << 1 | 1].l + 1) * tree[root].lazy;
        }
        return ;
    }
    inline void push_up(int root){
        tree[root].sum = tree[root << 1].sum + tree[root << 1 | 1].sum;
        tree[root].maxs = max(tree[root << 1].maxs, tree[root << 1 | 1].maxs);
        tree[root].mins = min(tree[root << 1].mins, tree[root << 1 | 1].mins);
        return ;
    }
    void build(int root, int l, int r){
        tree[root].l = l, tree[root].r = r, tree[root].lazy = 0;
        if(l == r){
            tree[root].sum = tree[root].maxs = tree[root].mins = tree_arr[l];
            return ;
        }
        int mid = (l + r) >> 1;
        build(root << 1, l, mid);
        build(root << 1 | 1, mid + 1, r);
        push_up(root);
    }
    void update(int root, int l, int r, int val){
        if(l <= tree[root].l && tree[root].r <= r){
            tree[root].sum += (tree[root].r - tree[root].l + 1) * val;
            tree[root].maxs += val;
            tree[root].mins += val;
            return ; 
        }
        push_down(root);
        int mid = (tree[root].l + tree[root].r) >> 1;
        if(l > mid){
            update(root << 1 | 1, l, r, val);
        }
        else if(r <= mid){
            update(root << 1, l, r, val);
        }
        else{
            update(root << 1, l, mid, val);
            update(root << 1 | 1, mid + 1, r, val);
        }
        push_up(root);
    }
    int query_sum(int root, int l, int r){
        if(tree[root].l >= l && tree[root].r <= r){
            return tree[root].sum;
        }
        push_down(root);
        int mid = (tree[root].l + tree[root].r) >> 1;
        if(r <= mid){
            return query_sum(root << 1, l, r);
        }
        else if(l > mid){
            return query_sum(root << 1 | 1, mid + 1, r);
        }
        else{
            return query_sum(root << 1, l, mid) + query_sum(root << 1 | 1, mid + 1, r);
        }
    }
}seg;
void TreeSum(int x, int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(deep[top[x]] < deep[top[y]]) swap(x, y);
        ans = (ans + seg.query_sum(1, id[top[x]], id[x])) % p;
        x = fa[top[x]];
    }
    if(deep[x] > deep[y]) swap(x, y);
    ans = (ans + seg.query_sum(1, id[x], id[y])) % p;
    cout << ans << endl;
}
/*why the height deep is go to your top ? */
void TreeAdd(int x, int y, int val){
    while(top[x] != top[y]){
        if(deep[top[x]] < deep[top[y]]) swap(x, y);
        seg.update(1, id[top[x]], id[x], val);
        x = fa[top[x]];
    }
    if(deep[x] > deep[y]) swap(x, y);
    seg.update(1, id[x], id[y], val);
}
void SubtreeSum(int x){
    cout << seg.query_sum(1, id[x], id[x] + size[x] - 1) % p << endl;
}
void SubtreeAdd(int x, int val){
    seg.update(1, id[x], id[x] + size[x] - 1, val % p);
}
struct LJ{
    int u, v, w;
}hzb[200005];
int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m >> r;
    e.Init();
    for(int i = 0; i < n - 1; i ++){
        cin >> hzb[i].u >> hzb[i].v >> hzb[i].w;
        e.add(hzb[i].u, hzb[i].v);
    }
    dfs1(r, 0, 1);
    dfs2(r, r);
    seg.build(1, 1, n);
    for(int i = 0; i < n - 1; i ++){
        int xs;
        if(deep[hzb[i].u] < deep[hzb[i].v]){
            xs = deep[hzb[i].v];
        }
        else{
            xs = deep[hzb[i].u];
        }
        seg.update(1, id[xs], id[xs], hzb[i].w);
    }
    
    return 0;
}