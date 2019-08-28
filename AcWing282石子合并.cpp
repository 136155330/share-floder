#include <bits/stdc++.h>
using namespace std;
const int MAXN = 305;
int arr[MAXN], sum[MAXN], dp[MAXN][MAXN];
int n;
int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> arr[i];
    }
    memset(dp, 0x3f, sizeof(dp));
    for(int i = 1; i <= n; i ++){
        sum[i] = sum[i - 1] + arr[i];
        dp[i][i] = 0;
    }
    for(int i = 2; i <= n; i ++){
        for(int l = 1; l <= n - i + 1; l ++){
            int r = l + i - 1;
            for(int k = l; k < r; k ++){
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
            }
            dp[l][r] += (sum[r] - sum[l - 1]);
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}