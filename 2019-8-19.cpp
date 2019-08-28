#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize(3)
map<string, int>M;
int cs;
string L;
string solve(string LL, int n, int num){
    LL.insert(n, 1, num + '0');
    char temp;
    int lnum, rnum, lsum, rsum;
    char temps;
    lnum = n, rnum = n;
    lsum = 0, rsum = 0;
    while (1) {
        int f = 0;
        temp = LL[lnum];
        temps = LL[rnum];
        if(temp != temps){
            break;
        }
        if(lnum == rnum){
            f = 1;
        }
        for (int i = lnum; i > -1; i--) {
            if (LL[i] == temp) {
                lsum++;
                lnum = i;
            } else {
                break;
            }
        }
        for (int i = rnum; i < LL.size(); i++) {
            if (LL[i] == temp) {
                rsum++;
                rnum = i;
            } else {
                break;
            }
        }
        if (lsum + rsum - f < 3) {
            lsum = rsum = 0;
            break;
        }
        for (int i = lnum; i <= rnum; i++) {
            LL[i] = '0';
        }
        lsum = rsum = 0;
        lnum = (lnum - 1 < 0 ? 0 : lnum - 1);
        rnum = (rnum + 1 >= LL.size() ? LL.size() : rnum + 1);
    }
    string HZBSTR;
    for(int i = 0; i < LL.length(); i ++){
        if(LL[i] != '0'){
            HZBSTR.push_back(LL[i]);
        }
    }
    return HZBSTR;
}
struct BFS_NODE{
    int value;
    string key;
    friend bool operator< (const BFS_NODE &a, const BFS_NODE &b){
        if(a.value != b.value)
        return a.value > b.value;
        else{
            return a.key.size() > b.key.size();
        }
    }
};
priority_queue<BFS_NODE>que;
int bfs(string LSS){
    BFS_NODE be;
    be.value = 0, be.key = LSS;
    que.push(be);
    while(!que.empty()){
        BFS_NODE te = que.top();
        que.pop();
        M[te.key] ++;
        if(te.key.size() == 0){
            return te.value;
        }
        if(te.value >= 4){
            return -1;
        }
        BFS_NODE en;
        for(int i = 0; i <= te.key.size(); i ++){
            for(int j = 1; j <= 3; j ++){
                en.key = solve(te.key, i, j);
                en.value = te.value + 1;
                if(en.key.size() == 0){
                    return en.value;
                }
                if(en.value >= 4 && en.key.size() > 0){
                    continue;
                }
                if(M.count(en.key)){
                    continue;
                }
                que.push(en);
                M[en.key] ++;
            }
        }
    }
    return -1;
}
int main(){
    #ifdef moxins
    freopen("C://Users//user//Desktop//A_1.in", "r", stdin);
    freopen("C://Users//user//Desktop//A_1.out", "w", stdout);
    #endif
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    string str;
    cin >> str;
    int re = bfs(str);
    cout << re << endl;
    return 0;
}