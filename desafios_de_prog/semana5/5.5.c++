#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

ll n, k, c;
vector<ll> v;
int dp [int(1e4)+1][int(1e4)+1];

ll rec(ll I, ll K) {
	for (int i = n; i >= 0; i--) {
		for (int k = 0; k <= K; k++) {
			if (i == n) {
					if (k == 0)
							dp[i][k] = 0;
					else
							dp[i][k] = -LINF;
					continue;
			}
			//colocando o lápis:
			ll best = -LINF;
			if (i + c <= n && k > 0)
					best = dp[i+c][k-1];

			//não colocando o lápis:
			ll skip = v[i] + dp[i+1][k];

			dp[i][k] = max(best, skip);
		}
	}

	return dp[I][K];
}

void solution() {
    cin >> n >> k >> c;
	v.resize(n);
    for (ll &i: v)
        cin >> i;

	cout << rec(0, k) << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();

	return 0;
}