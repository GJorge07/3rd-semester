#include <bits/stdc++.h>
#include <vector>
#include <queue>

using namespace std;

int N, M, T;
int aridez[1000][1000];
int ignicao[1000][1000];
int vizinhos_acesos[1000][1000]; // Conta quantos vizinhos 0 o pixel tem

struct Pixel {
    int r, c, t;
    bool operator>(const Pixel& o) const { return t > o.t; }
};

// 8-vizinhança para aridez 1
int dr8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// 4-vizinhança para aridez 2, 3, 4
int dr4[] = {-1, 1, 0, 0};
int dc4[] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> T;

    priority_queue<Pixel, vector<Pixel>, greater<Pixel>> pq;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> aridez[i][j];
            ignicao[i][j] = -1;
            vizinhos_acesos[i][j] = 0;
            if (aridez[i][j] == 0) {
                ignicao[i][j] = 0;
                pq.push({i, j, 0});
            }
        }
    }

    while (!pq.empty()) {
        Pixel atual = pq.top();
        pq.pop();

        if (atual.t > ignicao[atual.r][atual.c] && ignicao[atual.r][atual.c] != -1) {
            if (atual.t > T) break; 
        }

        // Tentar propagar para vizinhos de Aridez 1 (8-vizinhança)
        for (int i = 0; i < 8; i++) {
            int nr = atual.r + dr8[i], nc = atual.c + dc8[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M && aridez[nr][nc] == 1 && ignicao[nr][nc] == -1) {
                ignicao[nr][nc] = atual.t + 1;
                pq.push({nr, nc, ignicao[nr][nc]});
            }
        }

        // Tentar propagar para vizinhos de Aridez 2, 3, 4 (4-vizinhança)
        for (int i = 0; i < 4; i++) {
            int nr = atual.r + dr4[i], nc = atual.c + dc4[i];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                int tipo = aridez[nr][nc];
                if (tipo >= 2 && tipo <= 4 && ignicao[nr][nc] == -1) {
                    vizinhos_acesos[nr][nc]++;
                    int necessidade = (tipo == 2 ? 1 : (tipo == 3 ? 2 : 3));
                    if (vizinhos_acesos[nr][nc] >= necessidade) {
                        ignicao[nr][nc] = atual.t + 1;
                        pq.push({nr, nc, ignicao[nr][nc]});
                    }
                }
            }
        }
    }

    long long acesos = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (ignicao[i][j] != -1 && ignicao[i][j] <= T) {
                acesos++;
            }
        }
    }

    cout << acesos << endl;

    return 0;
}