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
        string s;   
        cin >> s;
        int n;
        cin >> n;
        set<int> st;
        for(int i = 0; i < s.size(); i++) {
            st.insert(i);
        }
        st.insert(-1);
        // cout << st.size() << "\n";
        //     auto it = lower_bound(st.begin(), st.end(), -1);
        //     cerr << *(it) << "\n";

        int deletions = 0;
        int sz = s.size();
        int index = n;
        while(index-sz > 0) {
            deletions++;
            index -= sz;
            sz--;
        }
        // return 0;
        int i = 0;
        while(deletions && i < s.size()) {
            
            auto it = st.lower_bound(i);
            // return 0; 
            it--;
            // cerr << *(it) << "\n";
            // return 0; 
            if(*it != -1 && s[*it] > s[i]) {
                s[*it] = '.';
                st.erase(*it);
                deletions--;
            }
            else i++;
        }
        // return 0;
        for(auto &c : s){
            if(c!='.') index--;
            if(!index) {
                cout << c;
                break;
            }
        }

    }
    return 0;
}
