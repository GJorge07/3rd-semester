#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<pair<int,int>> edges(M);
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        edges[i] = {a, b};
    }

    vector<pair<int,int>> broken(K);
    set<pair<int,int>> removed;

    for (int i = 0; i < K; i++) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        broken[i] = {a, b};
        removed.insert({a, b});
    }

    DSU dsu(N);
    int components = N;

    // Adiciona inicialmente só as arestas que NÃO serão quebradas
    for (auto [a, b] : edges) {
        if (!removed.count({a, b})) {
            if (dsu.unite(a, b)) {
                components--;
            }
        }
    }

    vector<int> ans(K);

    // Processa as quebras ao contrário
    for (int i = K - 1; i >= 0; i--) {
        ans[i] = components; // estado depois da i-ésima quebra

        auto [a, b] = broken[i];
        if (dsu.unite(a, b)) {
            components--;
        }
    }

    for (int i = 0; i < K; i++) {
        cout << ans[i] << (i + 1 == K ? '\n' : ' ');
    }

    return 0;
}