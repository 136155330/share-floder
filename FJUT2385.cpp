#include <bits/stdc++.h>
#define debug
using namespace std;
const int MAXN = 305;
int arr[MAXN * 2], sum[MAXN * 2], dp[MAXN * 2][MAXN * 2];
int n;
int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> arr[i];
    }
    for(int i = n + 1; i <= 2 * n; i ++){
        arr[i] = arr[i - n];
    }
    #ifdef debug
    for(int i = 1; i <= 2 * n; i ++){
        cout << arr[i] << " ";
    }
    cout << endl;
    #endif
    memset(dp, 0x3f, sizeof(dp));
    for(int i = 1; i <= 2 * n; i ++){
        sum[i] = sum[i - 1] + arr[i];
        dp[i][i] = 0;
    }
    int ans = 0x7fffffff;
    for(int i = 2; i <= n; i ++){
        for(int l = 1; l <= 2 * n - i + 1; l ++){
            int r = l + i - 1;
            for(int k = l; k < r; k ++){
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
            }
            dp[l][r] += (sum[r] - sum[l - 1]);
        }
    }
    for(int i = 1; i <= n; i ++){
        ans = min(ans, dp[i][i + n - 1]);
    }
    cout << ans << endl;
    return 0;
}