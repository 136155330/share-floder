# CDQ分治学习笔记
    什么是CDQ分治呢？
    CDQ分治，从一维的角度来考虑问题，那么就是归并排序
    那么为什么叫CDQ分治不叫归并排序呢？
## <1>
    1.我们考虑一个题目，给出一个数组，有n个元素，涉及m次操作，其中有单点更新操作与区间查询
    有点经验的同学已经想到了使用树状数组/线段树来解决问题，如果不使用这两种数据结构能否解决
    问题呢？
    我们先来考虑insert 操作 与 query 操作
    我们考虑一个问题，没错insert会影响后续的query操作
    那么query出来的结果应该是 前面insert对后面造成的影响
    我们可以先获取所有的操作
    然后通过归并排序，从低往上更新，然后可得对应查询的结果
    附上例题
[例题1](http://www.fjutacm.com/Problem.jsp?pid=1244)
    【思路】:我们可以先考虑怎么处理插入，查询的操作，通过前面的分析我们可以知道插入肯定会影响后序的查询
    那么我们要怎么实现区间呢？现将区间分成两个点【l,r】，可以变成对应的前缀和sum[r] - sum[l - 1]
    可以处理一个结构题
```C++
struct NODE{
    int type, idx;
    ll val;
    ///type代表数据的类型：是查询节点，还是插入节点 查询节点分为两种 一个是r， 一个是l
    ///对应1 3 2
    ///idx代表编号
    ///val是代表插入的更新的值，或者当前是第几个查询
}
```
    然后可以进行CDQ分治，怎么分治呢？
    考虑type的种类，更新肯定要在前面，然后考虑idx如果种类相同idx肯定要在前面
    然后使用一个sum来保存当前的值
    详细看代码理解
```C++
void CDQ(int l, int r){
    if(l + 1 < r){
        return ;
    }///当前只有一个元素
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid, r);
    int p, q;
    p = l, q = r;
    long long sum = 0;
    vector<NODE>vec;
    while(p < mid && q < r)///注意是[)区间
    {
        if(arr[p] < arr[q]){
            sum += arr[p].val;
            vec.push_back(arr[p]);
            p ++;
        }
        else{
            if(arr[q].type == 2) ans[arr[q].val] -= sum;
            else if(arr[q].type == 3) ans[arr[q].val] += sum;
            vec.push_back(arr[q]);
            q ++;
        }
    }
    while(p < mid){
        vec.push_back(arr[p ++]);
    }
    while(q < r){
        if(arr[q].type == 2) ans[arr[q].val] -= sum;
        else if(arr[q].type == 3) ans[arr[q].val] += sum;
        vec.push_back(arr[q]);
        q ++;
    }
    for(int i = 0; i < vec.size(); i ++){
        arr[l + i] = vec[i];
    }
    /**
     * 一层一层向上递归
     * 然后把每次的贡献加上去
     * 这样就能保证答案是对的
     * 因为每次都是左区间作用于右区间
     * 然后因为是1 1向上去递归的
     * 所以所有的影响都会被考虑
     * 时间复杂度是O(nlogn)
     * **/
}
```

附上代码：

```C++
#include <bits/stdc++.h>
using namespace std;
/*
CDQ分治
*/
const int MAXN = 50000 + 5;
int n, m;
typedef long long LL;
struct query {
    int type, idx;
    LL val;
    friend bool operator<(const query& a, const query& b) {
        return a.idx == b.idx ? a.type < b.type : a.idx < b.idx;
    }
} arr[MAXN << 2];
query temp[MAXN << 2];
LL ans[MAXN << 2];
void CDQ(int l, int r){
    if(r - l <= 1){
        return ;
    }
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid, r);
    int p = l, q = mid, tot = 0;
    LL sum = 0;
    while(p < mid && q < r){
        if(arr[p] < arr[q]){
            if(arr[p].type == 1) sum += arr[p].val;
            temp[tot ++] = arr[p ++];
        }
        else{
            if(arr[q].type == 2) ans[arr[q].val] -= sum;
            else if(arr[q].type == 3) ans[arr[q].val] += sum;
            temp[tot ++] = arr[q ++]; 
        }
    }
    while(p < mid){
        temp[tot ++] = arr[p ++];
    }
    while(q < r){
        if(arr[q].type == 2) ans[arr[q].val] -= sum;
        else if(arr[q].type == 3) ans[arr[q].val] += sum;
        temp[tot ++] = arr[q ++]; 
    }
    for(int i = 0; i < tot; i ++){
        arr[l + i] = temp[i];
    }
}
vector<int>vec;
int main() {
    ios::sync_with_stdio(false);
    int T, cnt = 0;
    cin >> T;
    int cases = 0;
    while(T --){
        memset(ans, 0, sizeof(ans));
        vec.clear();
        int n;
        cin >> n;
        cnt = 0;
        for(int i = 1; i <= n; i ++){
            int num;
            cin >> num;
            arr[cnt].idx = i, arr[cnt].type = 1, arr[cnt ++].val = num;
        }
        int ans_num = 0;
        while(1){
            string str;
            cin >> str;
            if(str == "Query"){
                int l, r;
                cin >> l >> r;
                vec.push_back(ans_num);
                arr[cnt].idx = r, arr[cnt].type = 3, arr[cnt ++].val = ans_num;
                arr[cnt].idx = l - 1, arr[cnt].type = 2, arr[cnt ++].val = ans_num ++;
            }
            else if(str == "Add"){
                int c, value;
                cin >> c >> value;
                arr[cnt].idx = c, arr[cnt].type = 1, arr[cnt ++].val = value;
            }
            else if(str == "Sub"){
                int c, value;
                cin >> c >> value;
                arr[cnt].idx = c, arr[cnt].type = 1, arr[cnt ++].val = -value;
            }
            else{
                break;
            }
        }
        CDQ(0, cnt);
        cout << "Case " << ++cases << ":\n";
        for(int i = 0; i < vec.size(); i ++){
            cout << ans[vec[i]] << endl;
        }
    }
    return 0;
}

```

## <2>

    2.刚刚考虑的一维的，那我们来考虑使用CDQ分治来解决二维偏序问题
    先附上例题
[例题2](http://www.fjutacm.com/Problem.jsp?pid=3926)
