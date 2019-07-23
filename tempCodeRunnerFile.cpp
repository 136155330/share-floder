#include <bits/stdc++.h>
using namespace std;
vector<int> vec[35];
int main() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) {
        vec[s[i] - 'a'].push_back(i);
    }
    for (int j = 0; j < 26; j++) {
        if(k == 0){
            break;
        }
        for (int z = 0; z < vec[j].size(); z++) {
            s[vec[j][z]] = '.';
            k --;
            if(k == 0){
                break;
            }
        }
        if(k == 0){
            break;
        }
    }
    for(int i = 0; i < s.length(); i ++){
        if(s[i] == '.'){
            continue;
        }
        else{
            cout << s[i];
        }
    }
    cout << endl;
    return 0;
}