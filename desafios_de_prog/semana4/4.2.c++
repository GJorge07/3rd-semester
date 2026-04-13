#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void solution() {
	ll n,m;
	cin >> n >> m;

	multiset<ll> ms;
	for (int i=0 ; i<n ; i++) {
		ll x;
		cin >> x;
		ms.insert(x);
	}


	for (int i=0 ; i<m ; i++) {
		ll temp;
		cin >> temp;

		auto it = ms.upper_bound(temp);

		if (it == ms.begin())
			cout << -1 << endl;
		else {
			it--;
			cout << *it << endl;
			ms.erase(it);
		}

	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();

	return 0;
}