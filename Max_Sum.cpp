#include <bits/stdc++.h>
using namespace std;
int vids[205];
int main(){
    ios::sync_with_stdio(false);
    string s, t;
    cin >> s >> t;
    int re = 0;
    for(int i = 0; i < s.length(); i ++){
        memset(vids, 0, sizeof(vids));
        int l = 0;
        for(int j = i; j < s.length(); j ++){
            if(s[j] == t[l]){
                l ++;
                vids[j] = 1;
                if(l == t.length()){
                    break;
                }
            }
        }
        if(l == t.length()){
            int len = 0;
            for(int j = 0; j < s.length(); j ++){
                if(vids[j] == 0){
                    len ++;
                }
                else{
                    re = max(re, len);
                    len = 0;
                }
            }
            re = max(re, len);
        }
    }
    cout << re << endl;
    return 0;
}