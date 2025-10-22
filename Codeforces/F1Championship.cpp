#include <bits/stdc++.h>
using namespace std;
# define int long long int
# define POW2(x) (1LL << (x))

map<int, string> mp;

map<string, int> id;

map<int, map<int, int>> points;

map<int, int> totalPoints;

map<int, int> firstPlace;

void solve() {

    int timer = 0;

    int t;
    cin >> t;

    int arr[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

    while(t--) {
        int n;
        cin >> n;
        for(int i = 0; i < n; i++) {
            string s;
            cin >> s;
            if(id.find(s) == id.end()) {
                id[s] = timer;
                mp[timer] = s;
                timer++;
            }
            if(i < 10) {
                points[id[s]][i]++;
                totalPoints[id[s]] += arr[i];
                if(i == 0) firstPlace[id[s]]++;
            }
            else {
                points[id[s]][i]++;
            }
        }
    }
    // now find the winner
    // type - 1
        // 1st get maximum point
    int maxpt = -1;
    for(auto &[_, pt] : totalPoints) {
        maxpt = max(maxpt, pt);
    }
    vector<int> winners;
    for(auto &[_, pt] : totalPoints) {
        if(pt == maxpt) winners.push_back(_);
    }
    int match = 0;
    while(winners.size() != 1) {
        int maxwin = 0;
        for(auto &winer : winners) {
            maxwin = max(maxwin, points[winer][match]);
        }
        vector<int> aw;
        for(auto &winer : winners) {
            if(points[winer][match] == maxwin) {
                aw.push_back(winer);
            }
        }
        swap(winners, aw);
        match++;
    }
    cout << mp[winners[0]] << "\n";
    // type - 2
        // get the max wins
    int maxwins = 0;
    for(auto &[_,win] : firstPlace) {
        maxwins = max(maxwins, win);
    }
    winners.clear();
    for(auto &[_,win] : firstPlace) {
        if(maxwins == win) winners.push_back(_);
    }
    if(winners.size() == 1){
        cout << mp[winners[0]] << "\n";
        return;
    }
    maxpt = -1;
    vector<int> tempWin;
    for(auto &win : winners) {
        maxpt = max(maxpt, totalPoints[win]);
    }
    for(auto &win : winners) {
        if(maxpt == totalPoints[win]) tempWin.push_back(win);
    }
    swap(winners, tempWin);
    match = 0;
    while(winners.size() != 1) {
        int maxwin = 0;
        for(auto &winer : winners) {
            maxwin = max(maxwin, points[winer][match]);
        }
        vector<int> aw;
        for(auto &winer : winners) {
            if(points[winer][match] == maxwin) {
                aw.push_back(winer);
            }
        }
        swap(winners, aw);
        match++;
    }
    cout << mp[winners[0]] << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    while(t--) solve();
}
