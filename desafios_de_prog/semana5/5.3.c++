#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

vector<ll> v;
unordered_map<int, unordered_map<int, int>> adj;
ll dp[1<<18][18];
ll N, M, K;

ll rec(ll mask, ll ult, ll escolhido) {
	if (escolhido == M)
		return 0;

	if (ult != -1 && dp[mask][ult] != -1)
		return dp[mask][ult];

	ll best = 0;
	for (ll nxt=0 ; nxt < N ; nxt++) {
		if (!(mask & (1<<nxt))) {
			ll gain = v[nxt];
			if (ult != -1)
				gain += adj[ult][nxt];
			best = max(best, gain + rec(mask | (1<<nxt), nxt, escolhido+1));
		}
	}
	if (ult != -1)
		dp[mask][ult] = best;
	return best;
}

void solution() {
	cin >> N >> M >> K;
	v.resize(N);

	for (ll &i: v)
		cin >> i;

	for (ll i=0 ; i<K ; i++) {
		ll xi, yi, ci;
		cin >> xi >> yi >> ci;
		xi--;
		yi--;
		adj[xi][yi] = ci;
	}

	memset(dp, -1, sizeof(dp));

	ll ans = 0;
	for (int i=0 ; i< N ; i++) {
		ans = max(ans, v[i] + rec(1<<i, i, 1));
	}

	cout << ans << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
