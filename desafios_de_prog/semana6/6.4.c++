#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int dist[MAXN];

// Função BFS que retorna o nó mais distante e sua distância
pair<int, int> bfs(int inicio, int n) {
    for (int i = 1; i <= n; i++) dist[i] = -1;
    
    queue<int> q;
    q.push(inicio);
    dist[inicio] = 0;
    
    int noMaisDistante = inicio;
    int maxDist = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        if (dist[u] > maxDist) {
            maxDist = dist[u];
            noMaisDistante = u;
        }
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return {noMaisDistante, maxDist};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Passo 1: Encontrar uma extremidade (U)
    pair<int, int> p1 = bfs(1, n);
    
    // Passo 2: Encontrar a outra extremidade (V) partindo de U
    pair<int, int> p2 = bfs(p1.first, n);

    // O diâmetro é a distância encontrada no segundo passo
    cout << p2.second << endl;

    return 0;
}