#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, C, K;

    while (cin >> N >> M >> C >> K) {
        vector<vector<pair<int,int>>> adj(N);

        for (int i = 0; i < M; i++) {
            int u, v, p;
            cin >> u >> v >> p;
            adj[u].push_back({v, p});
            adj[v].push_back({u, p});
        }

        vector<int> dist(N, INF);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[K] = 0;
        pq.push({0, K});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            if (u == C - 1) break;

            // Se estiver na rota, só pode ir para u+1
            if (u < C - 1) {
                for (auto [v, w] : adj[u]) {
                    if (v == u + 1) {
                        if (dist[v] > dist[u] + w) {
                            dist[v] = dist[u] + w;
                            pq.push({dist[v], v});
                        }
                        break; // só existe uma aresta útil aqui
                    }
                }
            }
            else {
                // Fora da rota, pode ir para qualquer vizinho
                for (auto [v, w] : adj[u]) {
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        cout << dist[C - 1] << '\n';
    }

    return 0;
}