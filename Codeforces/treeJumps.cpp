#include <bits/stdc++.h>
using namespace std;

#define    int             long long int
#define    debug2(x_, y_)  if(debug_out)cerr << x_ << ' ' << y_ << endl;
#define    debug1(x_)      if(debug_out)cerr << x_ << endl;
#define    all_rev(v)      v.rbegin(), v.rend()
#define    INT(x_)         int x_; cin >> x_ ;
#define    all(v)          v.begin(), v.end()
#define    SORT(v)         sort(all(v)); 

bool debug_out = true;
bool multi = true;

using Edge = int;

const int MOD  = 998244353;
const int MAXN = 13e6 + 6;
const int inf  = 1e16;
const int N    = 26;

vector<pair<int, int>> edges;
vector<vector<int>> factors;
vector<vector<Edge>> graph;
vector<bool> is_visited;
vector<bool> on_stack;
vector<int> fact;

int binpow(int base, int power){
    base %= MOD;
    int res = 1;
    while (power)
    {
        if(power % 2) res = (res * base) % MOD;
        power/=2;
        base = (base * base)%MOD;
    }
    return res;
}

int mod_inv(int base){
    return binpow(base, MOD-2);
}

void preprocess(){
    fact.assign(MAXN+1, 0);
    fact[0] = 1;
    for(int i = 1; i <= MAXN; i++){
        fact[i] = (fact[i-1]*i) % MOD;
    }
}

int nCr(int n, int r){
    if (r < 0 || r > n) return 0;
    int denom = (fact[r] * fact[n - r]) % MOD;
    return (fact[n] * mod_inv(denom)) % MOD;
}

void preprocess_sieve(){
    factors.assign(MAXN, vector<int>());
    for(int i = 1; i < MAXN; i++)
    {
        for(int t = i; t < MAXN; t+=i)
        {
            factors[t].push_back(i);
        }
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    if(multi) cin >> t;
    while(t--){
        int n;
        cin >> n;
        graph.assign(n, vector<Edge>());
        for(int i = 1; i < n; i++) {
            int x;
            cin >> x; x--;
            graph[x].push_back(i);
        }
        
        // root is 0

        vector<int> a(n, 0);
        a[0] = 1;
        map<int, int> mp; // level sum
        mp[0] = 1;
        int level = 1;
        queue<int> q;

        for(auto &v : graph[0]) {
            q.push(v);
            a[v] = 1;
            mp[level]++;
        }
        
        while(!q.empty())  {
            int x = q.size();
            while(x--) {
                int u = q.front(); q.pop() ;
                for(auto &v : graph[u]) {
                    q.push(v);
                    a[v] = (mp[level]-a[u] + MOD)%MOD;
                    mp[level+1] = (mp[level+1] + a[v]) % MOD;
                }
            }   
            level++;
        }
        
        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans = (ans + a[i])%MOD;
        }
        cout << ans << "\n";
    }
    return 0;
}