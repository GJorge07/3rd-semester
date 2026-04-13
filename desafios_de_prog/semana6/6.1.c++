#include <bits/stdc++.h>
#include <vector>

using namespace std;

// Lista de adjacência para representar o grafo
vector<int> adj[1005];
bool visitado[1005];

// Função DFS para percorrer todos os amigos que usam o mesmo editor
void dfs(int u) {
    visitado[u] = true;
    for (int v : adj[u]) {
        if (!visitado[v]) {
            dfs(v);
        }
    }
}

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    // Lendo as M amizades (mesmo editor)
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int numeroDeFestas = 0;

    // O número de festas é o número de componentes conexas
    for (int i = 0; i < N; i++) {
        if (!visitado[i]) {
            numeroDeFestas++;
            dfs(i); // Visita todos do mesmo grupo
        }
    }

    cout << numeroDeFestas << endl;

    return 0;
}