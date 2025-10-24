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
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        vector<int> indices(n - 1);
        iota(indices.begin(), indices.end(), 1); 

        vector<int> candidates(n);
        iota(candidates.begin(), candidates.end(), 1);

        for(int bit = 0; bit <= 25; bit++) {
            if(candidates.size() == 1) break;
            int x = (1LL << bit);
            vector<int> indices_with, indices_without;
            vector<int> candidates_with, candidates_without;
            int queried_count = 0; 
            int total_count = 0; 
            for(int c : candidates) {
                if ((c & x) > 0) {
                    candidates_with.push_back(c);
                    total_count++;
                } 
                else {
                    candidates_without.push_back(c);
                }
            }
            if (candidates_with.empty() || candidates_without.empty()) {
                continue;
            }
            for(int i : indices) {
                cout << "? " << i << " " << x << "\n"; cout.flush();
                int b;
                cin >> b;
                if (b == 1) {
                    indices_with.push_back(i);
                    queried_count++;
                }
                else {
                    indices_without.push_back(i);
                }
            }
            if (queried_count == total_count) {
                indices = indices_without;
                candidates = candidates_without;
            } 
            else {
                indices = indices_with;
                candidates = candidates_with;
            }
        }

        cout << "! " << candidates[0] << "\n"; cout.flush();
    }
    return 0;
}
