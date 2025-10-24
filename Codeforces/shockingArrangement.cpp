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
        int n;
        cin >> n;
        vector<int> a(n, 0);
        int M = -1;
        int m = inf;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            m = min(m, a[i]);
            M = max(M, a[i]);
        }

        bool all_zeros = true;
        for(int i = 0; i < n; i++) {
            if(a[i]) all_zeros = false;
        }
        if(all_zeros) {
            cout << "NO\n";
            continue;
        }

        priority_queue<int, vector<int>, greater<int>> pos;
        priority_queue<int, vector<int>, greater<int>> neg;
        int sum = 0;

        for(int i = 0; i < n; i++) {    
            if(a[i] < 0) {
                neg.push(a[i]);
            } 
            else {
                pos.push(a[i]);
            }
        }

        vector<int> ans;

        bool flag = true;

        for(int i = 0; i < n; i++) {
            if(!pos.empty())
                if(abs(sum + pos.top()) >= (M - m)) {
                    if(!neg.empty())
                        {   if(abs(sum + neg.top()) < (M-m))
                                {sum += neg.top(); ans.push_back(neg.top()); neg.pop();}
                            else 
                                {flag = false; break;}
                        }
                    else 
                        {flag = false; break;}
                }
                else{
                    sum += pos.top(); ans.push_back(pos.top()); pos.pop();
                }
            else {
                sum += neg.top(); ans.push_back(neg.top()); neg.pop();
                if(abs(sum) >= (M-m)) {
                    flag = false;
                    break;
                }
            }
        }
        if(!flag) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
            for(int i = 0; i < n; i++) {
                cout << ans[i] << " ";
            }
            cout << "\n";
        } 
    }
    return 0;
}