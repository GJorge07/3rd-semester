#include <bits/stdc++.h>
using namespace std;

vector<long long> dijkstra(int start, const vector<vector<pair<int, long long>>>& adj, int N) {
    vector<long long> dist(N, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, long long>>> adj(N);
    vector<tuple<int, int, long long>> edges;

    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges.push_back({u, v, w});
    }

    // Dijkstra de 0 e de N-1
    vector<long long> dist_from_0 = dijkstra(0, adj, N);
    vector<long long> dist_from_end = dijkstra(N - 1, adj, N);

    long long shortest_path = dist_from_0[N - 1];
    long long flower_length = 0;

    // Verificar cada aresta se ela faz parte de algum caminho mais curto
    for (auto [u, v, w] : edges) {
        if ((dist_from_0[u] != LLONG_MAX && dist_from_end[v] != LLONG_MAX &&
             dist_from_0[u] + w + dist_from_end[v] == shortest_path) ||
            (dist_from_0[v] != LLONG_MAX && dist_from_end[u] != LLONG_MAX &&
             dist_from_0[v] + w + dist_from_end[u] == shortest_path)) {
            flower_length += w;
        }
    }

    cout << flower_length * 2 << '\n';
    return 0;
}