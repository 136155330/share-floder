# B题
    题意: 给出一棵二叉树的中序、后序遍历，请你求出前序遍历。
    【思路】：首先我们分析可以发现后序遍历的最后一个肯定是根节点
    拿出根节点到中序序列去划分，可以得到左右子树，那么拿出倒二个后序遍历的值
    到左右子树去划分，可以得到左右子树对应的左右子树，递归到底
    出口是该左右子树的节点个数为一个，这样就构建了一棵二叉树
    对二叉树进行前序遍历，输出可以得到答案
    
## 前序中序后序的定义补充
![avatar](C:\\Users\\user\\Desktop\\123.png)

## 附上代码：
```C++
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
int tree[MAXN * 100], mid_tree[MAXN], end_tree[MAXN];
int n;
void dfs(int num, int root, int l, int r){///当前节点的数目 [l, r]
    int flag = 0;
    if(num == 0 || l > r || r < l){
        return ;
    }
    if(l == r){
        tree[root] = mid_tree[l];
        return ;
    }
    for(int i = l; i <= r; i ++){
        if(mid_tree[i] == end_tree[num]){
            flag = 1;
            dfs(num - 1, root * 2, l, i - 1);
            dfs(num - 1, root * 2 + 1, i + 1, r);
            tree[root] = mid_tree[i];
        }
    }
    if(!flag){
        dfs(num - 1, root, l, r);
    }
    return ;
}
void front_dfs(int root){///中左右
    cout << tree[root] << " ";
    if(tree[root * 2] != -1){
        front_dfs(root * 2);
    }
    if(tree[root * 2 + 1] != -1){
        front_dfs(root * 2 + 1);
    }
}
int main(){
    int n;
    cin >> n;
    memset(tree, -1, sizeof(tree));
    for(int i = 1; i <= n; i ++){
        cin >> mid_tree[i];
    }
    for(int i = 1; i <= n; i ++){
        cin >> end_tree[i];
    }
    dfs(n, 1, 1, n);
    front_dfs(1);
    cout << endl;
    return 0;
}
```