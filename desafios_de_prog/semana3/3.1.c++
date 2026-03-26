#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;
 
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int n,c;
vector<vector<int>> adj;
vector<int> indeg;

void gen(vector<int>& curr, vector<int>& indeg, vector<bool>& used) {
	if ((int)curr.size() == n) {
		for (int i = 0; i < n; i++) {
			cout << curr[i];
			if (i != n-1)
				cout << " ";
		}
		cout << endl;
		return;
	}

	vector<int> disp;
	for (int i=1 ; i<=n ; i++)
		if (!used[i] && indeg[i] == 0)
			disp.pb(i);

	sort(disp.begin(), disp.end());
	for (int u : disp) {
		curr.pb(u);
		used[u] = true;
		for (int v: adj[u])
			indeg[v]--;
		gen(curr, indeg, used);
		for (int v: adj[u])
			indeg[v]++;
		used[u] = false;
		curr.pop_back();
	}
}

void solution() {
	cin >> n >> c;
	adj.assign(n+1, vector<int>());
	indeg.assign(n+1, 0);
	for (int i=0 ; i<c ; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].pb(b);
		indeg[b]++;
	}
	vector<bool> used(n+1, false);
	vector<int> curr;
	gen(curr, indeg, used);
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solution();
	return 0;
}
