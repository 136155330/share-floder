#include <bits/stdc++.h>
//#define moxin
using namespace std;
char maps[505][505];
int vids[505][505];
vector<int>vec[505 * 505];
int n, m, k;
int in[505];
bool judge(int x, int y){
    if(x >= 0 && x <= n - 1 && y >= 0 && y <= m - 1 && maps[x][y] != '#'){
        return true;
    }
    return false;
}
int Get_num(int x, int y){
    return x * m + y;
}
int moves[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
struct NODE{
    int num, value;
    friend bool operator< (const NODE &a, const NODE &b){
        return a.value > b.value;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i = 0; i < n; i ++){
        scanf("%s", &maps[i]);
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            if(maps[i][j] == '.'){
                int num = Get_num(i, j);
                for(int z = 0; z < 4; z ++){
                    int x, y;
                    x = i + moves[z][0], y = j + moves[z][1];
                    if(judge(x, y)){
                        in[num] ++, in[Get_num(x, y)] ++;
                        vec[num].push_back(Get_num(x, y));
                        vec[Get_num(x, y)].push_back(num);
                        vids[num][Get_num(x, y)] = vids[Get_num(x, y)][num] = 1;
                    }
                }
            }
        }
    }
    priority_queue<NODE>que;
    for(int i = 0; i < n * m; i ++){
        if(vec[i].size()){
            in[i] /= 2;
            sort(vec[i].begin(), vec[i].end());
            vec[i].erase(unique(vec[i].begin(), vec[i].end()), vec[i].end());
            NODE t;
            t.num = i, t.value = in[i];
            if(in[i] == 1)
            que.push(t);
        }
    }
    #ifdef moxin
    for(int i = 0; i <= n * m; i ++){
        if(vec[i].size() != 0){
            cout << "in = " << in[i] << endl;
        cout << "i = " << i << endl;
        for(int j = 0; j < vec[i].size(); j ++){
            cout << vec[i][j] << " ";
        }
        cout << "\n";}
    }
    #endif
    while(k){
        NODE x = que.top();
        que.pop();
        maps[x.num / m][x.num % m] = '#';
        for(int i = 0; i < vec[x.num].size(); i ++){
            if(in[vec[x.num][i]] > 1){
                in[vec[x.num][i]] --;
                if(in[vec[x.num][i]] == 1){
                    NODE t;
                    t.num = vec[x.num][i];
                    t.value = 1;
                    que.push(t);
                }
            }
        }
        k --;
    }
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            cout << maps[i][j];
        }
        cout << endl;
    }
    return 0;
}