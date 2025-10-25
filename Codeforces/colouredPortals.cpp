#include<bits/stdc++.h>
using namespace std;

#define int long long int

vector<pair<int, int>> edges;

int32_t main() {
    ios_base :: sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        int n, q;
        cin >> n >> q;
        vector<string> a(n, "");

        map<string, vector<int>> mp;

        for(int i = 0; i < n; i++) {
            cin >> a[i];
            sort(a[i].begin(), a[i].end());
            mp[a[i]].push_back(i);
        }

        while(q--) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            bool flag = false;
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    if(a[u][i] == a[v][j]) {
                        flag = true;
                        break;
                    }
                }
            }
            if(flag) {
                cout << abs(u-v) << "\n";
            }
            else {
                int ans = 1e10;
                int x = min(u, v);
                int y = max(u, v);
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        string p = "";
                        p+=a[x][i];
                        p+=a[y][j];
                        sort(p.begin(), p.end());
                        // find some string that matches p
                        if(mp.find(p) != mp.end()) {
                            
                            flag = true;
                            int k;
                            // if any element bwn x and y -> y-x;

                            if(mp[p].back() > x && mp[p][0] < y) {
                                auto it1 = upper_bound(mp[p].begin(), mp[p].end(), x);
                                if(*it1 < y) {
                                    ans = y-x;
                                }
                            }

                            // if bfr x -> y - k;
                            if(mp[p][0] < x){
                                auto it1 = lower_bound(mp[p].begin(), mp[p].end(), x);
                                it1--;
                                k = *it1;
                                ans = min(ans, y-k + x-k);
                            }
                            
                            // if afr y -> k - x;

                            if(mp[p].back() > y) {
                                auto it1 = upper_bound(mp[p].begin(), mp[p].end(), y);
                                k = *it1;
                                ans = min(ans, k-x + k-y);
                            }
                        }
                    }
                }
                if(ans == 1e10) ans = -1;
                cout << ans << "\n" ;
            }
        }

    }
}
