# 2019-7-23手速赛

    该题想法：根据均分纸牌的思想，我可以知道绕行给值肯定不是最优解
    那么我们可以知道改变已经确定的值肯定不是最优解的一部分，那么正
    向给牌肯定是最优解的组成
    举个例子：1 -> 4  4 -> 1 这样肯定是最优的解
    那么我们可以先预处理出所有的值的数量
    把多出来的值放到一个空余的数组中
    如果当前的值的数量是不足的呢？那么我们可以从空余数组中去取
    从尾部开始取，因为尾部肯定是最接近当前的值的数
    那么处理的时候顺带改变数组中的值，就可以ac这道题啦

```C++
#include <bits/stdc++.h>
using namespace std;
/*
x % m == C[i] == [0 .... m - 1] 
vector<int>[] <- 对应的编号放进去
1.如果已经满足了，就没有必要去变化
2.从小的变化为大的肯定是优秀的

把多的对应丢到vector<pair<int, int>>

*/
const int MAXN = 2 * 1e5 + 5;
int arr[MAXN];
queue<int>vec[MAXN];
int main(){
    int n, m;
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; i ++){
        cin >> arr[i];
        vec[arr[i] % m].push(i);///vec - 编号
    }
    vector<pair<int, int> >vecs;
    long long re = 0;
    for(int i = 0; i < 2 * m; i ++){
        int num = i % m;
        while(vec[num].size() > n / m){
           int x = vec[num].front();
           vec[num].pop();
           vecs.push_back(make_pair(x, i));
        }
        while(vec[num].size() < n / m && !vecs.empty()){
            pair<int, int>temp = vecs.back();
            vecs.pop_back();
            if(temp.second < num){
                re += (num - temp.second);
                arr[temp.first] += (num - temp.second);
            }
            else{
                re += (num - temp.second + m);
                arr[temp.first] += (num - temp.second + m);
            }
            vec[num].push(temp.first);
        }
    }
    cout << re << endl;
    for(int i = 0; i < n; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}
```