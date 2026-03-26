#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void solution() {
	int n;
	cin >> n;

	vector<ll> v(n);
	for (ll &i: v)
		cin >> i;

	sort(v.begin(), v.end());

	ll m1 = v[1]/v[0];
	ll m2 = v[2]/v[1];
	ll m3 = v[3]/v[2];

	ll q = m1+m2+m3-max({m1,m2,m3})-min({m1,m2,m3});

	ll soma_vetor = accumulate(v.begin(), v.end(), 0LL);

	ll a1 = v[0];

	ll rn1 = 1;
	for (int i=1 ; i<=n ; i++) rn1 *= q;


	ll s_pgn1;
	if (q==1) {
		cout << v[0] << endl;
		return;
	}
	else
		s_pgn1 = (a1 *(rn1 -1)) / (q-1);

	if (s_pgn1 == soma_vetor) {
		set <ll> ans;
		if (v[0] % q == 0) ans.insert(v[0]/q);
		ans.insert(v.back()*q);
		for (auto x : ans) cout << x << endl;
	}
	else {
		rn1 *= q;
		ll s_pgn2 = (q==1) ? a1* (n+1) : (a1 * (rn1 - 1)) / (q-1);
		ll diff = s_pgn2 - soma_vetor;
		cout << diff << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();

	return 0;
}
