#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define pb push_back
typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

int N, I, M, P;
vector<int> v;
vector<int> c;
vector<vector<int>> dp;
vector<vector<int>> choice;

/*int rec(int i, int N) {
	if (N == 0)
		return 0;

	if (dp[i][N] != -1)
		return dp[i][N];

	if (i == M)
		return dp[i][N] = rec(1, N-1) + P - v[i-1] + c[0];

	int best = INF;
	if (i != 0)
		best = rec(1, N-1) + P - v[i-1] + c[0];

	int skip = rec(i+1, N-1) + c[i];

	if (best == skip)
		return dp[i][N] = best;

	return dp[i][N] = min(best, skip);
}*/

int rec() {
	dp.assign(M+1, vector<int>(N+1, 0));
	choice.assign(M+1, vector<int>(N+1, 0));


	for (int i=0 ; i<=M ; i++)
		dp[i][0] = 0;

	for (int k=1 ; k<=N ; k++) {
		for (int u=M ; u>=0 ; u--) {
			int resp = INF;

			if (u==M) {
				resp = dp[1][k-1] + P - v[u-1] + c[0];
				choice[u][k] = 1;
			}
			else {
				int best = INF;
				if (u != 0)
					best = dp[1][k-1] + P - v[u-1] + c[0];

				int skip = dp[u+1][k-1]+c[u];

				if (best <= skip) {
					resp = best;
					choice[u][k] = 1;
				}
				else {
					resp = skip;
					choice[u][k] = 0;
				}
			}

			dp[u][k] = resp;
		}
	}

	return dp[I][N];
}


void solution() {
	cin >> N >> I >> M >> P;
	v.resize(M);	
	c.resize(M);

	for (int &i : c) cin >> i;
	for (int &i : v) cin >> i;

	int resp = rec();
	cout << resp << endl;

	int idade = I;
	int anos = N;
	vector<int> trocados;
	for (int o=1 ; o<=N ; o++) {
		if (choice[idade][anos] == 1) {
			trocados.pb(o);
			idade = 1;
		}
		else
			idade++;
		anos--;
	}

	if (trocados.empty())
		cout << 0 << endl;
	else {
	for (int t : trocados)
		cout << t << " ";
	cout << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	solution();

	return 0;
}
