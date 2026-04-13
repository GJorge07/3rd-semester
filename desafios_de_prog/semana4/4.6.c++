#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void solution() {
	ll n;
	cin >> n;

	vector<pair<ll, ll>> v(9);
	pair<ll, ll> menor;
	menor.first = LLONG_MAX;
	for (ll i=0 ; i<9 ; i++) {
		ll temp;
		cin >> temp;
		v[i] = {temp, i+1};
		if (temp <= menor.first) {
			menor.first = temp;
			menor.second = i+1;
		}
	}

	ll qntd_alg = n/menor.first;
	ll resto = n % menor.first;

	for (ll k=0 ; k<qntd_alg ; k++) {
		ll mlhr_digito = menor.second, mlhr_cost = menor.first;
		for (ll u=menor.second-1 ; u<9 ; u++) {
			if ((v[u].second > menor.second && resto+menor.first >= v[u].first)) {
				mlhr_digito = v[u].second;
				mlhr_cost = v[u].first;
			}
		}
		cout << mlhr_digito;
		resto += menor.first - mlhr_cost;
	}
	cout << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();

	return 0;
}
