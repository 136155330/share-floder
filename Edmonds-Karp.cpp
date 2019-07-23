#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 10050;
const int inf = 0x7fffffff;
struct E_K{
    int tot, s, t, maxflow;///输入s, t
    struct NODE{
        int u, v, w, next;
    }arr[MAXM << 1];
    int head[MAXN];
    void Edge_Init(){
        tot = 0;
        memset(arr, 0, sizeof(arr));
        memset(head, -1, sizeof(head));
    }
    void add_edge(int u, int v, int w){
        arr[tot].u = u, arr[tot].v = v, arr[tot].w = w, arr[tot].next = head[u];
        head[u] = tot;
        tot ++;
    }
    void EK_add(int u, int v, int w){
        add_edge(u, v, w);
        add_edge(v, u, 0);
    }
    int vids[MAXN], incf[MAXN], pre[MAXN];
    void EK_Init(){
        memset(incf, 0, sizeof(incf));
        memset(pre, 0, sizeof(pre));
        maxflow = 0;
    }
    bool bfs(){
        memset(vids, 0, sizeof(vids));
        queue<int> que;
        que.push(s);
        vids[s] = 1;
        incf[s] = inf;
        while(!que.empty()){
            int x = que.front();
            que.pop();
            for(int i = head[x]; ~i; i = arr[i].next){
                if(arr[i].w && !vids[arr[i].v]){
                    int y = arr[i].v;
                    incf[y] = min(incf[x], arr[i].w);///寻找管道可以经过的最小流量
                    pre[y] = i;
                    que.push(y), vids[y] = 1;
                    if(y == t){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void update(){
        int x = t;
        while(x != s){
            int num = pre[x];
            arr[num].w -= incf[t];
            arr[num ^ 1].w += incf[t];///反向的流量，反悔边
            x = arr[num ^ 1].v;
        }
        maxflow += incf[t];
    }
    int EK_algorithm(){
        while(bfs()){
            update();
        }
        return maxflow;
    }
}EK;
int main(){
    int t, step;
    ios::sync_with_stdio(false);
    cin >> t;
    step = 0;
    while(t --){
        int n, m;
        cin >> n >> m;
        EK.Edge_Init();
        EK.EK_Init();
        EK.s = 1, EK.t = n;
        for(int i = 0; i < m; i ++){
            int u, v, w;
            cin >> u >> v >> w;
            EK.EK_add(u, v, w);
        }
        int re = EK.EK_algorithm();
        cout << "Case " << ++ step << ": " << re << endl;
    }
    return 0;
}