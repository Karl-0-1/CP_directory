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

        int n, m, v;

        cin >> n >> m >> v;

        vector<int> a(n+2, 0);

        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        vector<int> prefixSm(n+2, 0);

        for(int i = 1; i <= n+1; i++) {
            prefixSm[i] = prefixSm[i-1] + a[i];
        }

        // make prefix and suffix windows and then gather the sums 

        vector<int> pre(n+2, 0), suff(n+2, 0);
        
        int s = 0;
        for(int i = 1; i <= n; i++) {
            s += a[i];
            if(s >= v) {
                s = 0;
                pre[i] = 1;
            }
        }
        s = 0;
        for(int i = n; i>=1; i--) {
            s += a[i];
            if(s >= v) {
                s = 0;
                suff[i] = 1;
            }
        }
        s = 0;
        for(int i = 1; i <= n; i++) {
            pre[i] += pre[i-1];
        }
        for(int i = n; i >= 1; i--) {
            suff[i] += suff[i+1];
        }

        map<int, int> index;
        for(int i = 1; i <= n+1; i++) {
            index[suff[i]] = i;
        }

        if(pre[n] < m && suff[1] < n) {
            cout << -1 << "\n" ; continue;
        }
        // start from index 1;
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            int bk = pre[i-1];
            int need = max((int)0, m-bk);
            // debug1(need);
            // now
            if(index.find(need) != index.end()) {
                int l = i;
                int r = index[need] - 1;
                if(r >= l) {
                    ans = max(ans, prefixSm[r]-prefixSm[l-1]);
                }
                // debug2(l, r)
            }

        }
        
        cout << ans << "\n";
        
    }
    return 0;
}
