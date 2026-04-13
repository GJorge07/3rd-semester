#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// Estrutura para facilitar a manipulação de coordenadas
struct Pos {
    int r, c;
};

int N, M;
char mapa[1000][1000];
char rastro[1000][1000]; // Guarda a direção 'L', 'R', 'U', 'D' usada para chegar aqui
bool visitado[1000][1000];

// Direções: Cima, Baixo, Esquerda, Direita
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
char dirChar[] = {'U', 'D', 'L', 'R'};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Pos inicio, fim;
    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> mapa[i][j];
            if (mapa[i][j] == 'A') inicio = {i, j};
            if (mapa[i][j] == 'B') fim = {i, j};
        }
    }

    queue<Pos> q;
    q.push(inicio);
    visitado[inicio.r][inicio.c] = true;

    bool encontrou = false;
    while (!q.empty()) {
        Pos atual = q.front();
        q.pop();

        if (atual.r == fim.r && atual.c == fim.c) {
            encontrou = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = atual.r + dr[i];
            int nc = atual.c + dc[i];

            // Verifica limites e se é passável
            if (nr >= 0 && nr < N && nc >= 0 && nc < M && 
                mapa[nr][nc] != '#' && !visitado[nr][nc]) {
                
                visitado[nr][nc] = true;
                rastro[nr][nc] = dirChar[i]; // Guarda como chegamos aqui
                q.push({nr, nc});
            }
        }
    }

    if (encontrou) {
        cout << "YES" << endl;
        
        // Reconstrói o caminho de trás para frente
        string caminho = "";
        Pos curr = fim;
        while (curr.r != inicio.r || curr.c != inicio.c) {
            char d = rastro[curr.r][curr.c];
            caminho += d;
            
            // Move para a célula anterior baseada na direção inversa
            if (d == 'U') curr.r++;
            else if (d == 'D') curr.r--;
            else if (d == 'L') curr.c++;
            else if (d == 'R') curr.c--;
        }
        
        reverse(caminho.begin(), caminho.end());
        cout << caminho.size() << endl;
        cout << caminho << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}