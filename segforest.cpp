#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
struct Segforest{
    int head[MAXN];
    int tot = 0;
    struct NODE{
        int l, r, ls, rs, sum;
        ///ls, rs指向
    }arr[MAXN * 30];
    void Init(){
        memset(head, 0, sizeof(head));
        tot = 0;
    }
    int build(int l, int r){
        int p = tot ++;
        arr[p].l = l, arr[p].r = r;
        if(l == r){
            arr[p].sum = 1;
            return p;
        }
        int mid = (l + r) >> 1;
        arr[p].ls = build(l, mid);
        arr[p].rs = build(mid + 1, r);
        arr[p].sum = arr[arr[p].ls].sum + arr[arr[p].rs].sum;
        return p;
    }
    int update(int now, int pos, int val){
        int p = tot ++;
        arr[p] = arr[now];
        if(arr[p].l == arr[p].r){
            arr[p].sum += val;
            return p;
        }
        int mid = (arr[p].l + arr[p].r) >> 1;
        if(pos <= mid){
            arr[p].ls = update(arr[p].ls, pos, val);
        }
        else{
            arr[p].rs = update(arr[p].rs, pos, val);
        }
        arr[p].sum = arr[arr[p].ls].sum + arr[arr[p].rs].sum;
        return p;
    }
    int query(int begins, int ends, int k){
        if(arr[begins].l == arr[ends].r){
            return arr[begins].l;
        }
        int cnt = (arr[arr[ends].ls].sum - arr[arr[begins].ls].sum);
        if(k <= cnt){
            return query(arr[begins].ls, arr[ends].ls, k);
        }
        else{
            return query(arr[begins].rs, arr[ends].rs, k);
        }
    }
}forest;
int arr[MAXN];
int main(){
    int T;
    scanf("%d", &T);
    while(T --){
        int n, m;
        scanf("%d%d", &n, &m);
        forest.Init();
        for(int i = 0; i < n; i ++){
            scanf("%d", &arr[i]);
        }
        forest.head[0] = forest.build(1, n + 1);
        for(int i = 0; i < n; i ++){
            forest.head[i + 1] = forest.update(forest.head[i], arr[i], -1);
        }
        int x = n + 1;
        int lastans = 0;
        for(int i = 0; i < m; i ++){
            int a, b, c;
            scanf("%d", &a);
            if(a == 1){
                scanf("%d", &b);
                b = b ^ lastans;
                forest.head[x] = forest.update(forest.head[x - 1], b, -1);
                x ++;
            }
            else{
                scanf("%d%d", &b, &c);
                b = b ^ lastans, c = c ^ lastans;
                lastans = forest.query(forest.head[b - 1], forest.head[x - 1], 1);
                printf("%d\n", lastans);
            }
        }
    }
    return 0;
}