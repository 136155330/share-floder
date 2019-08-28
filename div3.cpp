#include <bits/stdc++.h>
using namespace std;
const int MAXN = 150000 + 5;
int arr[MAXN], vids[MAXN];
int main(){
    int n;
    cin >> n;
    int mins = MAXN;
    int maxs = 0;
    for(int i = 0; i < n; i ++){
        cin >> arr[i];
        vids[arr[i]] ++;
        mins = min(mins, arr[i]);
        maxs = max(maxs, arr[i]);
    }
    for(int i = maxs; i >= mins; i --){
        if(vids[i] > 1){
            if(i - 1 > 0){
                vids[i - 1] ++;
                vids[i] --;
            }
        }
        if(vids[i] > 1){
                vids[i + 1] ++;
                vids[i] --;
        }
    }
    int ans = 0;
    for(int i = 1; i < MAXN; i ++){
        if(vids[i]){
            ans ++;
        }
    }
    cout << ans << endl;
    return 0;
}