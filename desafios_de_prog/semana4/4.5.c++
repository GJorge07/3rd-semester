#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int solution() {
	ll n, a;
	cin >> n >> a;
	if (n == 0 && a == 0)
		return -1;

	vector<ll> v(n);
	for (ll &i: v) cin >> i;

	ll soma_total = accumulate(v.begin(), v.end(), 0LL);

	if (soma_total < a) {
		cout << "-.-" << endl;
		return 0;
	}
	if (soma_total == a) {
		cout << ":D" << endl;
		return 0;
	}

	double l=0;
	double r=*max_element(v.begin(), v.end());
	double ans = -1;
	for (int i=0 ; i<100 ; i++) {
		double m = (l+r) / 2;
		double area = 0;
		for (int j=0 ; j<n ; j++) {
			if (v[j] > m)
				area += v[j]-m;
		}
		if (fabs(area - a) < 1e-5) {
			ans = m;
			break;
		}
		if (area > a)
			l = m;
		else
			r = m;
	}
	if (ans < 0)
		ans = l;
	cout << fixed << setprecision(4) << ans << endl;

	return 0;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	while (true) {
		int res = solution();
		if (res != 0)
			break;
	}
 
	return 0;
}
