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
bool multi = false;

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
        int n;
        cin >> n;
        vector<int> a(n+1, 0); 

        for(int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        queue<pair<int, int>> q;
        vector<int> b(n+1, 1);

        for(int i = n; i >= 1; i--) {
            int me = a[i];
            b[me] = 0;
            // now how many less than these were there now (double)

            for(int i = me-1; i >= 1; i--) {
                if(b[i]) {
                    q.push({me, i});
                }
            }
            
            for(int i = 1; i < me; i++) {
                if(b[i]) {
                    q.push({i, me});
                }
            }

            // now how many greater than these are there now (single)

            for(int i = me + 1; i <= n; i++) {
                if(b[i]) {
                    q.push({i, me});
                }
            }

        }

        cout << q.size() << "\n";

        while(!q.empty()) {
            auto [u, v] = q.front(); q.pop();
            cout << u << " " << v << "\n";
        }

    }
    return 0;
}