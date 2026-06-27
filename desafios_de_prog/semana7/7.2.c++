#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    vector<int> L(N+1);
    for(int i = 1; i <= N; i++) cin >> L[i];
    
    int M;
    cin >> M;
    
    vector<tuple<int,int,int>> edges;
    for(int i = 0; i < M; i++){
        int x, y;
        cin >> x >> y;
        edges.push_back({x, y, L[y] - L[x]});
    }
    
    const long long INF = 1e18;
    vector<long long> dist(N+1, INF);
    dist[1] = 0;
    
    // Bellman-Ford
    for(int iter = 0; iter < N-1; iter++){
        bool updated = false;
        for(auto& [u, v, w] : edges){
            if(dist[u] != INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if(!updated) break;
    }
    
    // Detectar nós afetados por ciclos negativos
    // Marcar todos alcançáveis a partir de ciclos negativos
    vector<bool> negInf(N+1, false);
    for(int iter = 0; iter < N; iter++){
        for(auto& [u, v, w] : edges){
            if(dist[u] != INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                negInf[v] = true;
            }
            if(negInf[u]) negInf[v] = true;
        }
    }
    
    int Q;
    cin >> Q;
    while(Q--){
        int x;
        cin >> x;
        long long ans;
        if(negInf[x]) ans = LLONG_MIN; // custo pode ir a -inf
        else ans = dist[x];
        
        if(ans == INF){
            // inalcançável - improvável dado o enunciado
            cout << "Não, Edsger...\n";
        } else if(negInf[x] || ans < 3){
            cout << "Não, Edsger...\n";
        } else {
            cout << ans << "\n";
        }
    }
    
    return 0;
}