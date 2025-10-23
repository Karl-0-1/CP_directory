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

bool f(vector<vector<vector<vector<int>>>> &dp, string &s, int i, bool is_guarded, bool is_pre_rabbit, bool is_open) { // is previous guarded
    if(i >= s.size()) {
        if(is_open){
            return s.back()!='1';
        } 
        else return true;
    }

    bool res = 0;
    if(dp[i][is_guarded][is_pre_rabbit][is_open]!=-1) return dp[i][is_guarded][is_pre_rabbit][is_open];
    if(s[i] == '0') {
        if(is_pre_rabbit) {
            // c-1 turn toward the rabbit and dont guard further
            res = res | f(dp, s, i+1, false, true, false);
            // c-2 turn rev and guard the next cell
            res = res | f(dp, s, i+1, true, true, true);
        }
        else if(is_guarded && !is_pre_rabbit) {
            if(i == 0)res = res | f(dp, s, i+1, false, true, false) | f(dp, s, i+1, true, true, true);
            else res = res | f(dp, s, i+1, false, true, false);
        }
        else if(!is_guarded && !is_pre_rabbit) {
            if(!is_open)
                res = res | f(dp, s, i+1, true, true, true);
        }
    }
    else {
        if(is_pre_rabbit && is_guarded) {
            res = res | f(dp, s, i+1, true, false, is_open);
        }
        else if (is_guarded && i!=0) {
            res = false;
            // res = res | f(dp, s, i+1, false, false, is_open);
        }
        else if(is_pre_rabbit) {
            res = res | f(dp, s, i+1, false, false, is_open);
        }
        else {
            res = res | f(dp, s, i+1, false, false, is_open);
        }
    }

    return dp[i][is_guarded][is_pre_rabbit][is_open] = res;
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
        string s;
        cin >> s;
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(2, vector<vector<int>>(2, vector<int>(2, -1))));
        if(f(dp, s, 0, true, false, false)) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
