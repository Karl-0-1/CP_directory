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

int32_t main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    if(multi) cin >> t;
    while(t--){
        int n, c;
        cin >> n >> c;
        vector<int> a(n+1, 0);
        int M = -1;
        map<int, int> mp;

        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            M = max(M, a[i]);
            mp[a[i]] ++;
        }
        vector<int> pre(n+1, 0);
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i-1] + a[i];
        }
        
        vector<int> ans(n+1, 0);

        // maintain max in right part 
        
        for(int i = 1; i <= n; i++) {
            mp[a[i]]--;
            if(mp[a[i]] == 0) {
                mp.erase(a[i]);
            }

            // find winning condition
            if(a[1] + c >= a[i]) {
                int val = a[i] + pre[i-1] + c;
                if(!mp.empty()) {
                    auto [value, ct] = *mp.rbegin();
                    if(value > val) {
                        ans[i] = i-1 + 1;
                    }
                    else {
                        ans[i] = i-1;
                    }
                }
                else {
                    ans[i] = n-1;
                }
            }
            else {
                // check if this is the maximum among all of the elements
                int val = pre[i] + c;
                if(a[i] == M) {
                    M = inf;
                    ans[i] = 0;
                }
                else {
                    if(!mp.empty()) {
                        auto [value, ct] = *mp.rbegin();
                        if(value > val) {
                            ans[i] = i-1 + 1;
                        }
                        else {
                            ans[i] = i-1;
                        }
                    }
                    else {
                        ans[i] = n-1;
                    }
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}