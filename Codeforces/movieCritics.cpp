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
bool multi = false;

using Edge = tuple<int, int>;

const int MOD  = 998244353;
const int MAXN = 13e6 + 6;
const int inf  = 1e16;
const int N    = 26;

vector<pair<int, int>> edges;
vector<vector<int>> factors;
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
        int n, k ;
        cin >> n >> k;
        vector<int> a(n+10, 0);
        vector<vector<int>> graph(n+10, vector<int>());
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            graph[a[i]].push_back(i);
        }

        int max_stress_removal = 0;
        int by = 0;

        for(int i = 1; i <= k; i++) {
            if(graph[i].size() == 0) continue;
            int k = 0;
            int removal = 0;
            while(k < graph[i].size()) {
                int y = graph[i][k] - 1;
                int start = a[graph[i][k] - 1];
                while(k < graph[i].size()-1 && (graph[i][k]+1 == graph[i][k+1])) {
                    k++;
                }
                int end = a[graph[i][k] + 1];

                int x = graph[i][k] + 1 ;

                // cerr << x << "\n";

                k++;
                
                if((start == end) && start && end) removal +=2;
                else if(start != end) removal ++;
                // if(start == 0 || end == 0) removal += 1;
                
                
            }
            if(max_stress_removal < removal) {
                
                max_stress_removal = removal;
                by = i;
            }
            debug2(removal, i);
        }
        
        if(max_stress_removal == 0) {
            cout << a[1] << "\n";
        }
        else {
            cout << by << "\n";
        }

    }
    return 0;
}
