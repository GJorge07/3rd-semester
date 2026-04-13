#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

vector<int> v = {1,5,10,25,50};
vector<vector<ll>> dp(300001, vector<ll> (5, -1));

ll rec(ll i, ll n) {
	if (n == 0)
		return 1;
	if (v[i] > n || i == v.size())
		return 0;

	if (dp[n][i] != -1)
		return dp[n][i];

	ll usa = rec(i, n-v[i]);
	ll skip = rec(i+1, n);

	return dp[n][i] = usa+skip;
}


void solution() {
	ll n;
	while(cin >> n) {
		cout << rec(0,n) << endl;
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
