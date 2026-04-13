#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

vector<bool> v(3, false);

void solution() {
	ll n;
	cin >> n;

	vector<ll> A(n), B(n), C(n);
	for (ll i=0 ; i<n ; i++)
		cin >> A[i] >> B[i] >> C[i];

	ll dp0 = A[0];
	ll dp1 = B[0];
	ll dp2 = C[0];

	for (ll i=1 ; i<n ; i++) {
		ll ndp0 = A[i] + max(dp1, dp2);
		ll ndp1 = B[i] + max(dp0, dp2);
		ll ndp2 = C[i] + max(dp0, dp1);
		dp0 = ndp0;
		dp1 = ndp1;
		dp2 = ndp2;
	}

	cout << max({dp0, dp1, dp2}) << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
