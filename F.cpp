#include <bits/stdc++.h>
using namespace std;
int main() {
    long long a, b, c, d, e, f;
    while (cin >> a >> b >> c >> d >> e >> f) {
        long long ans = 0;
        long long len1 = 2 * a + 1;
        for (int i = 0; i < min(b, f); i++) {
            ans += len1;
            len1 += 2;
        }
        len1 -= 2;
        for (int i = min(b, f); i < max(b, f); i++) {
#ifdef moxin
            cout << "len1 = " << len1 << endl;
            cout << ans << endl;
#endif
            ans += (len1 + 1);
        }

        long long len2 = 2 * d + 1;
        for (int i = 0; i < min(e, c); i++) {
            ans += len2;
            len2 += 2;
        }
        cout << ans << endl;
    }
    return 0;
}