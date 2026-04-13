#include <bits/stdc++.h>
#include <vector>

using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int sz[MAXN];
int n;

// Passo 1: Calcular o tamanho de cada subárvore
void calcular_tamanho(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            calcular_tamanho(v, u);
            sz[u] += sz[v];
        }
    }
}

// Passo 2: Encontrar o vértice cujos filhos não excedam n/2
int encontrar_centroide(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            // Se uma subárvore é maior que n/2, o centroide deve estar lá
            if (sz[v] > n / 2) {
                return encontrar_centroide(v, u);
            }
        }
    }
    // Se chegamos aqui, nenhuma subárvore "abaixo" é > n/2.
    // Como estamos descendo, a subárvore "acima" também será <= n/2.
    return u;
}

int main() {
    // Otimização de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    calcular_tamanho(1, 0);
    cout << encontrar_centroide(1, 0) << endl;

    return 0;
}