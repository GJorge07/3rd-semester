#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void solution() {
	ll p, h, f, d, c;
	cin >> p >> h >> f >> d >> c;


	ll count = 0;
	if (d > c) {
		while (p > 1 && h>0) {
			count += d;
			h--;
			p -= 2;
		}
		while (p > 1 && f>0) {
			count += c;
			f--;
			p -= 2;
		}
	}
	else {
		while (p > 1 && f>0) {
			count += c;
			f--;
			p -= 2;
		}
		while (p > 1 && h>0) {
			count += d;
			h--;
			p -= 2;
		}
	}

	cout << count << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin >> t;
	while(t--)
		solution();
 
	return 0;
}
