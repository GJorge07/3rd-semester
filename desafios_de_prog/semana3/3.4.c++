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

    ll result = LLONG_MAX;
	for (ll mask=0 ; mask < (1LL << (n-1)) ; mask++) {
        ll xor_total = 0;
        ll or_atual = w[0];
        
        for (int k=0 ; k < (n-1) ; k++) {
            if (mask & (1LL << k)) {
                xor_total ^= or_atual;
                or_atual = w[k+1];
            }
            else
                or_atual |= w[k+1];
        }
        xor_total ^= or_atual;
        result = min(result, xor_total);
    }

    cout << result << endl;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}