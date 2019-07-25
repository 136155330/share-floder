#include <bits/stdc++.h>
using namespace std;
struct Dinic {
    static const int MAXN = 10005; ///改网络流的点
    static const int MAXM = MAXN; ///改网络流的边
    static const long long INF = __LONG_LONG_MAX__; ///看情况改
    int n, m, s, t;
    int first[MAXN], cur[MAXN];
    long long dist[MAXN];
    int sign;
    struct Node {
        long long to, flow, next;
    } edge[MAXM * 4];
    inline void init(int start, int vertex, int ss, int tt) {
        n = vertex, s = ss, t = tt;
        for(int i = start; i <= n; i++ ) {
            first[i] = -1;
        }
        sign = 0;
    }

    inline void add_edge(int u, int v, long long flow) {
        edge[sign].to = v, edge[sign].flow = flow, edge[sign].next = first[u];
        first[u] = sign++;
        edge[sign].to = u, edge[sign].flow = 0, edge[sign].next = first[v];
        first[v] = sign++;
    }

    inline long long dinic() {
        long long max_flow = 0;
        while(bfs(s, t)) {
            for(int i = 0; i <= n; i++ ) {
                cur[i] = first[i];
            }
            max_flow += dfs(s, INF);
        }
        return max_flow;
    }

    bool bfs(int s, int t) {
        memset(dist, -1, sizeof(dist));
        queue<int>que;
        que.push(s), dist[s] = 0;
        while(!que.empty()) {
            int now = que.front();
            que.pop();
            if(now == t) {
                return 1;
            }
            for(int i = first[now]; ~i; i = edge[i].next) {
                int to = edge[i].to;
                long long flow = edge[i].flow;
                if(dist[to] == -1 && flow > 0) {
                    dist[to] = dist[now] + 1;
                    que.push(to);
                }
            }
        }
        return 0;
    }


    long long dfs(int now, long long max_flow) {
        if(now == t) {
            return max_flow;
        }
        long long ans = 0;
        long long next_flow = 0;
        for(int &i = cur[now]; ~i; i = edge[i].next) {
            int to = edge[i].to;
            long long flow = edge[i].flow;
            if(dist[to] == dist[now] + 1 && flow > 0) {
                next_flow = dfs(to, min(max_flow - ans, flow));
                ans += next_flow;
                edge[i].flow -= next_flow;
                edge[i ^ 1].flow += next_flow;
                if(ans == max_flow) {
                    return max_flow;
                }

            }
        }
        if(ans == 0) {
            return dist[now] = 0;
        }
        return ans;
    }
} dinic;

struct Dijkstra{
    int n;
    const long long inf = __LONG_LONG_MAX__;
    struct NODE{
        int u, v, next;
        long long w;
    }arr[10005];
    int tot = 0;
    int head[10005];
    long long dist1[10005], dist2[10005];
    void Init(){
        tot = 0;
        memset(arr, 0, sizeof(arr));
        memset(head, -1, sizeof(head));
    }
    void Init_dist1(){
        for(int i = 0; i < 10005; i ++){
            dist1[i] = inf;
        }
    }
    void Init_dist2(){
        for(int i = 0; i < 10005; i ++){
            dist2[i] = inf;
        }
    }
    void add(int u, int v, long long w){
        arr[tot].u = u, arr[tot].v = v, arr[tot].w = w;
        arr[tot].next = head[u];
        head[u] = tot;
        tot ++;
    }
    struct MYINT{
        int num;
        long long cost;
        friend bool operator<(const MYINT &a, const MYINT &b){
            return a.cost > b.cost;
        }
    };
    void bfs1(){
        int vids[10005];
        memset(vids, 0, sizeof(vids));
        MYINT be;
        be.num = 1, be.cost = 0;
        priority_queue<MYINT>que;
        que.push(be);
        vids[be.num] = 1;
        dist1[be.num] = 0;
        while(!que.empty()){
            MYINT te = que.top();
            que.pop();
            vids[te.num] = 1;
            for(int i = head[te.num]; ~i; i = arr[i].next){
                MYINT en = te;
                en.num = arr[i].v;
                if(!vids[arr[i].v] && en.cost + arr[i].w <= dist1[arr[i].v]){
                    en.cost += arr[i].w;
                    dist1[arr[i].v] = min(dist1[arr[i].v], en.cost);
                    que.push(en);
                }
            }
        }
    }
    void bfs2(){
        int vids[10005];
        memset(vids, 0, sizeof(vids));
        MYINT be;
        be.num = n, be.cost = 0;
        priority_queue<MYINT>que;
        que.push(be);
        vids[be.num] = 1;
        dist2[be.num] = 0;
        while(!que.empty()){
            MYINT te = que.top();
            que.pop();
            vids[te.num] = 1;
            for(int i = head[te.num]; ~i; i = arr[i].next){
                MYINT en = te;
                en.num = arr[i].v;
                if(!vids[arr[i].v] && en.cost + arr[i].w <= dist2[arr[i].v]){
                    en.cost += arr[i].w;
                    dist2[arr[i].v] = min(dist2[arr[i].v], en.cost);
                    que.push(en);
                }
            }
        }
    }
}dj;
struct NODE{
    int u, v;
    long long w;
}arr[10005];
/**
.init(点编号起点, 点编号终点, 源点, 汇点)
.add_edge(u, v, w) 加边
.dinic() 输出最大流
*/
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    int n, m;
    while(t --){
        cin >> n >> m;
        dj.n = n;
        dj.Init();
        dj.Init_dist1();
        dinic.init(1, n, 1, n);
        for(int i = 0; i < m; i ++){
            cin >> arr[i].u >> arr[i].v >> arr[i].w;
        }
        for(int i = 0; i < m; i ++){
            dj.add(arr[i].u, arr[i].v, arr[i].w);
        }
        dj.bfs1();
        dj.Init();
        dj.Init_dist2();
        for(int i = 0; i < m; i ++){
            dj.add(arr[i].v, arr[i].u, arr[i].w);
        }
        dj.bfs2();
        for(int i = 1; i <= n; i ++){
            cout << dj.dist1[i] << " ";
        }
        cout << endl;
        for(int i = 1; i <= n; i ++){
            cout << dj.dist2[i] << " ";
        }
        cout << endl;
        for(int i = 0; i < m; i ++){
            if(dj.dist1[arr[i].u] + dj.dist2[arr[i].v] + arr[i].w == dj.dist1[arr[i].v]){
                cout << arr[i].u << " " << arr[i].v << " ???" << arr[i].w << endl;
                dinic.add_edge(arr[i].u, arr[i].v, arr[i].w);
            }
        }
        long long re = dinic.dinic();
        cout << re << endl;
    }
    return 0;
}