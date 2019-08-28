#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 105;
LL dp[MAXN][32005];
struct NODE {
    LL v, p, q, id;
    friend bool operator<(const NODE &a, const NODE &b) {
        if (a.id != b.id)
            return a.id < b.id;
        else {
            return a.q < b.q;
        }
    }
} arr[MAXN];
LL w_arr[MAXN][3], v_arr[MAXN][3];
/*
0:代表主件的价值 1:代表附件一的价值 2:代表附件二的价值
*/
int n, m;
int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    int num = 0;
    for (int i = 0; i < m; i++) {
        cin >> arr[i].v >> arr[i].p >> arr[i].q;
        if (!arr[i].q) {
            arr[i].id = num++;
        } else {
            arr[i].id = arr[arr[i].q - 1].id;
        }
    }
    sort(arr, arr + m);
    vector<int> vec_w[MAXN], vec_v[MAXN];
    for (int i = 0; i < m; i++) {
        vec_w[arr[i].id].push_back(arr[i].p),
            vec_v[arr[i].id].push_back(arr[i].v);
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < vec_v[i].size(); j++) {
            w_arr[i][j] = vec_w[i][j];
            v_arr[i][j] = vec_v[i][j];
        }
    }
    for (int i = 1; i <= num; i++) {
        for (int j = n; j > 0; j--) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            if (j - v_arr[i - 1][0] >= 0)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - v_arr[i - 1][0]] +
                                             w_arr[i - 1][0] * v_arr[i - 1][0]);
            if (j - v_arr[i - 1][0] - v_arr[i - 1][1] >= 0)
                dp[i][j] = max(
                    dp[i][j], dp[i - 1][j - v_arr[i - 1][0] - v_arr[i - 1][1]] +
                                  w_arr[i - 1][0] * v_arr[i - 1][0] +
                                  w_arr[i - 1][1] * v_arr[i - 1][1]);
            if (j - v_arr[i - 1][0] - v_arr[i - 1][2] >= 0)
                dp[i][j] = max(
                    dp[i][j], dp[i - 1][j - v_arr[i - 1][0] - v_arr[i - 1][2]] +
                                  w_arr[i - 1][0] * v_arr[i - 1][0] +
                                  w_arr[i - 1][2] * v_arr[i - 1][2]);
            if (j - v_arr[i - 1][0] - v_arr[i - 1][1] - v_arr[i - 1][2] >= 0)
                dp[i][j] =
                    max(dp[i][j], dp[i - 1][j - v_arr[i - 1][0] -
                                            v_arr[i - 1][1] - v_arr[i - 1][2]] +
                                      w_arr[i - 1][0] * v_arr[i - 1][0] +
                                      w_arr[i - 1][1] * v_arr[i - 1][1] +
                                      w_arr[i - 1][2] * v_arr[i - 1][2]);
        }
    }
    LL ans = 0;
    for (int j = 0; j <= n; j++) {
        ans = max(ans, dp[num][j]);
    }
    cout << ans << endl;
    return 0;
}