#include <bits/stdc++.h>
using namespace std;

struct PairInfo {
    int dist;
    string src, dst;
    int u, v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    map<string, int> id;
    vector<string> name;
    vector<pair<string, string>> edges_input;
    edges_input.reserve(M);

    auto get_id = [&](const string& s) -> int {
        auto it = id.find(s);
        if (it != id.end()) return it->second;
        int idx = (int)name.size();
        id[s] = idx;
        name.push_back(s);
        return idx;
    };

    for (int i = 0; i < M; i++) {
        string a, b;
        cin >> a >> b;
        edges_input.push_back({a, b});
        get_id(a);
        get_id(b);
    }

    vector<vector<int>> adj(N);
    for (auto &[a, b] : edges_input) {
        int u = id[a];
        int v = id[b];
        adj[u].push_back(v);
    }

    // Ordenar vizinhos ajuda a reconstruir um caminho "organizado",
    // embora qualquer caminho mínimo seja aceito.
    for (int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end(), [&](int x, int y) {
            return name[x] < name[y];
        });
    }

    const int INF = 1e9;
    vector<PairInfo> pairs;
    long long sumDist = 0;
    long long totalPairs = 0;

    // BFS de cada origem
    for (int s = 0; s < N; s++) {
        vector<int> dist(N, INF);
        queue<int> q;
        dist[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        for (int t = 0; t < N; t++) {
            if (s != t && dist[t] != INF) {
                sumDist += dist[t];
                totalPairs++;
                pairs.push_back({dist[t], name[s], name[t], s, t});
            }
        }
    }

    sort(pairs.begin(), pairs.end(), [](const PairInfo& a, const PairInfo& b) {
        if (a.dist != b.dist) return a.dist < b.dist;
        if (a.src != b.src) return a.src < b.src;
        return a.dst < b.dst;
    });

    double average = (double)sumDist / (double)totalPairs;
    cout << fixed << setprecision(5) << average << '\n';

    // posição ceil(P/2), usando índice 0-based:
    long long idx = (totalPairs - 1) / 2;
    PairInfo med = pairs[idx];

    // Reconstruir um caminho mínimo do par mediano
    vector<int> dist(N, INF), parent(N, -1);
    queue<int> q;
    dist[med.u] = 0;
    q.push(med.u);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (dist[v] == INF) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    vector<int> path;
    for (int cur = med.v; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < (int)path.size(); i++) {
        if (i) cout << ' ';
        cout << name[path[i]];
    }
    cout << '\n';

    return 0;
}