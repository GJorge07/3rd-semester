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

	vector<ll> w(n);
	for (ll &temp: w)
		cin >> temp;

	ll total = accumulate(w.begin(), w.end(), 0LL);
	ll melhor_soma = INF;

	for (int i=0 ; i< (1 << n) ; i++) {
		ll soma = 0;
		for (int k=0 ; k<n ; k++) {
			if (i & (1 << k))
				soma += w[k];
		}
		ll temp = total-soma;
		melhor_soma = min(melhor_soma, abs(soma-temp));
	}

	cout << melhor_soma << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
