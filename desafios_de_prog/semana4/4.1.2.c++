#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAXN = 1e5 + 15;
ll n, h;
vector<ll> a(MAXN);
ll swaps = 0;

void merge_sort(int l, int r) {
	if (r - l == 1) { return; }
	int mi = l + (r - l) / 2;
	merge_sort(l, mi); merge_sort(mi, r);
	vector<ll> aux (r - l);
	int i = l, j = mi;
	for (int k = 0; k < r - l; k++) {
		if (i < mi && j < r) {
			if (!(a[i] < a[j])) {
				swaps += mi - i;
			}
			if (a[i] < a[j]) { aux[k] = a[i++];}
			else { aux[k] = a[j++]; }
		}
		else if (i < mi) { aux[k] = a[i++]; }
		else { aux[k] = a[j++]; }
	}
	copy(aux.begin(), aux.end(), a.begin()+l);
}


void solution() {
	cin >> n >> h;

	for (ll i=0 ; i<n ; i++)
		cin >> a[i];

	if (h > 1)
		merge_sort(0, h);
	swaps = 0;
	merge_sort(0 , n);

	cout << swaps << endl;

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();

	return 0;
}