#include <bits/stdc++.h>
using namespace std;
#define    int             long long int
#define    debug2(x_, y_)  if(debug_out)cerr << x_ << ' ' << y_ << endl;
#define    debug1(x_)      if(debug_out)cerr << x_ << endl;
#define    all_rev(v)      v.rbegin(), v.rend()
#define    INT(x_)         int x_; cin >> x_ ;
#define    all(v)          v.begin(), v.end()
#define    SORT(v)         sort(all(v)); 

bool debug_out = false;
bool multi = true;

using Edge = tuple<int, int>;

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

vector<int> dp;
vector<int> pre;
map<pair<int, int>, int> dp1;
int f(int i, int g, int x, vector<int> &a) {
    if(i >= a.size()) return 0;
    if(g+a[i] > x) {
        if(dp[i] != -1) return dp[i];
        return dp[i] = f(i+1, 0, x, a);
    }
    else {
        if(dp1.find({i, g}) != dp1.end()) return dp1[{i, g}];
        auto it = upper_bound(pre.begin(), pre.end(), pre[i-1]+x-g);
        int idx = it - pre.begin();
        int count = idx - i;
        return dp1[{i, g}] = count + f(idx+1, 0, x, a);
    }
}

int32_t main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    if(multi) cin >> t;
    while(t--){
        dp1 = map<pair<int, int>, int>();
        int n, x;
        cin >> n >> x;
        vector<int> a(n+1, 0);
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        dp.assign(n+10, -1);
        pre.assign(n+1, 0);
        for(int i = 1; i<= n; i++) {
            pre[i] = pre[i-1] + a[i];
        }
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            // cout << ans << "\n";
            ans += f(i, 0, x, a);
        }
        cout << ans << "\n";
    }
    return 0;
}
