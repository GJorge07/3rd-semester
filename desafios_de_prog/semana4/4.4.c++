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

	vector<string> v(n);
	for (string &i: v)
		cin >> i;

	sort(v.begin(), v.end(), [](const string &a, const string &b) {
		return a+b < b+a;
	});

	for (int i=0 ; i<n ; i++)
		cout << v[i];

	cout << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
