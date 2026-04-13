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


	ll count = 0;
	for (ll i=0 ; i<n ; i++) {
		ll temp;
		cin >> temp;
		if (temp > 10)
			count+=temp-10;
	}

	cout << count << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
