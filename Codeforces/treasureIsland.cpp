#include <bits/stdc++.h>
using namespace std;
# define int long long int
# define POW2(x) (1LL << (x))

int n, m;

char arr[1005][1005];
vector<pair<int, int>> path;

int hvz[1005][1005];
int vert[1005][1005];

bool check (int i, int j) {
    // start from here and check 
    int x = i;
    int y = j;
    for(auto &[dx, dy] : path) {
        int x1 = x+dx;
        int y1 = y+dy;

        if(dx == 0) {
            int ly = min(y, y1);
            int ry = max(y, y1);

            if(ly <= 0 || ry > m) return false;

            if(hvz[x][ry]-hvz[x][ly-1] != 0) return false;

        }
        else { // dy == 0
            int ux = min(x, x1);
            int dox = max(x, x1);

            if(ux <= 0 || dox > n) return false;

            if(vert[dox][y] - vert[ux-1][y]) return false;

        }
        
        x = x1;
        y = y1;

    }

    return true;
}

void solve() {
    memset(hvz, 0, sizeof hvz);
    memset(vert, 0, sizeof vert);
    
    cin >> n >> m;

    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for(int j = 1; j <= m; j++) {
            arr[i][j] = s[j-1];
            if(arr[i][j]=='#') {
                hvz[i][j] = 1;
                vert[i][j] = 1;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            hvz[i][j] += hvz[i][j-1];
            vert[i][j] += vert[i-1][j];
        }
    }

    int k;
    cin >> k;

    for(int i = 0; i < k; i++) {
        char c;
        cin >> c;
        int x;
        cin >> x;
        // mark directions reverse 
        if(c == 'N') {
            path.push_back({-x, 0});
        }
        else if(c == 'S') {
            path.push_back({+x, 0});
        }
        else if(c == 'E') {
            path.push_back({0, +x});
        }
        else {
            path.push_back({0, -x});
        }
    }
    vector<char> sol;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(arr[i][j] != '#' && arr[i][j] != '.') {
                if(check(i, j)) sol.push_back(arr[i][j]);
            }
        }
    }
    
    if(sol.empty()) {
        cout << "no solution";
    }
    else {
        sort(sol.begin(), sol.end());
        for(auto &c: sol){
            cout << c ;
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    while(t--) solve();
}
