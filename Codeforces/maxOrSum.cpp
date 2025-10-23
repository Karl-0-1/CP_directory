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

const int LOG = 33;

struct trie_node {
	trie_node* nodes[2];
    int count;
	trie_node() {
		nodes[0] = nodes[1] = nullptr;
        count = 0;
	}
};

struct TRIE {
	trie_node* root;
public :
	void insert(int val) {
		trie_node* temp = root;
        temp->count ++;
		for(int i = 0; i < LOG; i++) {
			int bit = (val >> i) & 1;
			if(temp->nodes[bit]) {
				temp = temp->nodes[bit];
                temp->count ++;
			}
			else {
				temp->nodes[bit] = new trie_node();
				temp = temp->nodes[bit];
                temp->count++;
			}
		}
	}	
	int query(int x) { // max xor
		int res = 0;
		trie_node* temp = root;
		for(int i = 0; i < LOG; i++) {
			int bit = (x >> i) & 1;
			if(temp->nodes[bit^1] && ((temp->nodes[bit^1]->count)> 0)) {
				res += (1 << i);
				temp = temp->nodes[bit^1];
			}
			else {
				temp = temp->nodes[bit];
			}
		}
		return res;
	}
	
    void remove(int x) {
		trie_node* temp = root;
        temp->count --;
		for(int i = 0; i < LOG; i++) {
			int bit = (x >> i) & 1;
			if(temp->nodes[bit]) {
				temp = temp->nodes[bit];
                temp->count--;
			}
			else {
				temp = temp->nodes[bit^1];
                temp->count--;
			}
		}
    }
 
	TRIE () {
		root = new trie_node();
	}
	
	// memory cleanup for memory leak risk
	void deleteTrie(trie_node* node) {
		if (!node) return;
		deleteTrie(node->nodes[0]);
		deleteTrie(node->nodes[1]);
		delete node;
	}

	~TRIE() {
		deleteTrie(root);
	}
};

int32_t main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    if(multi) cin >> t;
    while(t--){
        int l, r;
        cin >> l >> r;
        int n = r - l + 1;
        vector<int> a(n, 0);

        TRIE trie;
        for(int i = l; i <= r; i++) {
            trie.insert(i);
        }
        int s = 0;
        for(int i = l; i <= r; i++) {
            // for this i find the best match 
            int x = trie.query(i);
            x^=i;
            trie.remove(x);
            // find the best match => tries
            a[i-l] = x;
            s += (i | x);
        }
        cout << s << "\n";
        for(int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
