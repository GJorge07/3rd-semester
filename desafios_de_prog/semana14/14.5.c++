#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    int xr = 0;
    int maiores = 0;
    int idxMaior = -1;
    int uns = 0;

    for (int i = 0; i < N; i++) {
        cin >> A[i];
        xr ^= A[i];

        if (A[i] > 1) {
            maiores++;
            idxMaior = i;
        } else {
            uns++;
        }
    }

    // Caso especial: todos os montes têm tamanho 1
    if (maiores == 0) {
        if (N % 2 == 0) {
            cout << 1 << " " << 1 << "\n";
        } else {
            cout << -1 << "\n";
        }

        return 0;
    }

    // Caso especial: só existe um monte maior que 1
    if (maiores == 1) {
        int deixar;

        if (uns % 2 == 0)
            deixar = 1;
        else
            deixar = 0;

        int comer = A[idxMaior] - deixar;
        cout << comer << " " << idxMaior + 1 << "\n";
        return 0;
    }

    // Caso normal do Nim
    if (xr == 0) {
        cout << -1 << "\n";
        return 0;
    }

    for (int i = 0; i < N; i++) {
        int novo = A[i] ^ xr;

        if (novo < A[i]) {
            int comer = A[i] - novo;
            cout << comer << " " << i + 1 << "\n";
            return 0;
        }
    }

    return 0;
}