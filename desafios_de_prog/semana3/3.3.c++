#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void solution() {
	ll lim1, lim2;
	cin >> lim1 >> lim2;

	ll n;
	cin >> n;
	vector<ll> v(n);
	for (ll &i: v)
		cin >> i;

	ll total = lim2-lim1+1;

	ll count=0;
	for (ll mask=1 ; mask< (1<<n) ; mask++) {
		ll temp = 1;
		int par = 0;
		for (ll k=0 ; k<n ; k++) {
			if (mask & (1<<k)) {
				temp *= v[k];
				par++;
			}
		}
		ll mult = ((lim2/temp) - ((lim1-1)/temp));
		if (par % 2 == 0)
			count -= mult;
		else
			count += mult;
	}

	cout << total-count << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
