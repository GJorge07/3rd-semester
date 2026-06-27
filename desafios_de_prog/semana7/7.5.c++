#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    const int INF = 1e9;
    vector<vector<int>> dist(N, vector<int>(N, INF));

    for (int i = 0; i < N; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // Floyd-Warshall
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int answer = INF;

    for (int i = 0; i < N; i++) {
        int worst = 0;
        for (int j = 0; j < N; j++) {
            worst = max(worst, dist[i][j]);
        }
        answer = min(answer, worst);
    }

    cout << answer << '\n';

    return 0;
}