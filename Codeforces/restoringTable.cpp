#include <bits/stdc++.h>
using namespace std;
# define int long long int
# define POW2(x) (1LL << (x))

void solve() {
    int n;
    cin >> n;
    int a[n][n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> ans(n, 0);
    // GOT THE BASE ANSWER NOW CHECK AND BUILD
    while(true){ 
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                if(a[i][j] != (ans[i] & ans[j])) {
                    // check the missing bits
                    ans[i]|=a[i][j];
                    ans[j]|=a[i][j];
                }
            }
        }
        bool flag = true;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                if(a[i][j] != (ans[i] & ans[j])) {
                    // check the missing bits
                    ans[i]|=a[i][j];
                    ans[j]|=a[i][j];
                    flag = false;
                }
            }
        }
        if(flag) break;
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t =1;
    while(t--) solve();
}
