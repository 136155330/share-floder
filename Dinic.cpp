#include <bits/stdc++.h>
using namespace std;
/*
Dinic算法：
解决最大流最小割问题
复杂度O(m * sqrt(n))
 */
const int inf = 0x7fffffff;
const int MAXN = 1005;
const int MAXM = 10005;
int n, m;
struct Dinic{
    int tot, s, t, maxflow;
    int head[MAXN];
    struct NODE{
        int u, v, w, next;
    }arr[MAXM << 1];
    void Edge_Init(){
        memset(head, -1, sizeof(head));
        memset(arr, 0, sizeof(arr));
        tot = 0;
    }
    void add(int u, int v, int w){
        arr[tot].u = u, arr[tot].v = v, arr[tot].w = w;
        arr[tot].next = head[u];
        head[u] = tot;
        tot ++; 
    }
    void Dinic_add(int u, int v, int w){
        add(u, v, w);
        add(v, u, 0);
    }
    int dist[MAXN];
    void Dinic_Init(){
        maxflow = 0;
        memset(dist, 0, sizeof(dist));
    }
    bool bfs(){///在图上构造分层图
        memset(dist, 0, sizeof(dist));
        queue<int>que;
        while(!que.empty()) que.pop();
        que.push(s);
        dist[s] = 1;
        while(!que.empty()){
            int x = que.front(); que.pop();
            for(int i = head[x]; ~i; i = arr[i].next){
                if(arr[i].w && !dist[arr[i].v]){
                    que.push(arr[i].v);
                    dist[arr[i].v] = dist[x] + 1;
                    if(arr[i].v == t){
                        return true;
                    }
                }
            }
        } 
        return false;
    }
    int dfs(int x, int flow){
        if(x == t){
            return flow;
        }
        int rest = flow, k;
        for(int i = head[x]; ~i; i = arr[i].next){
            if(arr[i].w && dist[arr[i].v] == dist[x] + 1){
                k = dfs(arr[i].v, min(rest, arr[i].w));
                if(!k) dist[arr[i].v] = 0;
                arr[i].w -= k;
                arr[i ^ 1].w += k;
                rest -= k;
            }
        }
        return flow - rest;
    }
    int dinic_algorithm(){
        int flows = 0;
        while(bfs()){
            while(flows = dfs(s, inf)){
                maxflow += flows;
            }
        }
        return maxflow;
    }
}dc;
int main(){
    int t, step;
    ios::sync_with_stdio(false);
    cin >> t;
    step = 0;
    while(t --){
        int n, m;
        cin >> n >> m;
        dc.Dinic_Init();
        dc.Edge_Init();
        dc.s = 1, dc.t = n;
        for(int i = 0; i < m; i ++){
            int u, v, w;
            cin >> u >> v >> w;
            dc.Dinic_add(u, v, w);
        }
        int re = dc.dinic_algorithm();
        cout << "Case " << ++ step << ": " << re << endl;
    }
    return 0;
}