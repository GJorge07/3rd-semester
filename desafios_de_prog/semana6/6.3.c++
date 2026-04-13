#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAXIMO = 1e5+10;
vector<vector<int>> filhos(MAXIMO);
vector<bool> vivo(MAXIMO, false);
vector<int> ordem_s;
vector<int> pos(MAXIMO);
int idx_atual = 0;

void dfs(int u) {
	pos[u] = ordem_s.size();
	ordem_s.pb(u);
	for (int f : filhos[u])
		dfs(f);
}

void solution() {
	int q;
	cin >> q;

	vector<pair<int, int>> eventos(q);
	int count = 1;

	vivo[1] = true;

	for (int i=0 ; i<q ; i++) {
		cin >> eventos[i].first >> eventos[i].second;
		if (eventos[i].first == 1) {
			count++;
			filhos[eventos[i].second].pb(count);
			vivo[count] = true;
		}
	}

	dfs(1);

	for (int i=0 ; i<q ; i++) {
		int t = eventos[i].first;
		int x = eventos[i].second;

		if (t == 2) {
			vivo[x] = false;

			if (ordem_s[idx_atual] == x) {
				while (!vivo[ordem_s[idx_atual]])
					idx_atual++;
			}
			cout << ordem_s[idx_atual] << endl;
		}


	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();
 
	return 0;
}
