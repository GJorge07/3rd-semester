#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

unordered_map<ll, ll> memo;

ll f(ll x) {
	if (x == 0)
		return 1;
	if (memo.count(x))
		return memo[x];

	return memo[x] = (f(floor(x/2)) + f(floor(x/3)));
}

void solution() {
	ll x;
	cin >> x;
	ll resp = f(x);
	cout << resp << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
