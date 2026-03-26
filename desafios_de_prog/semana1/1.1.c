#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Função para verificar se um número (string) é par
bool isPar(const string& num) {
    if (num.empty()) return false;
    char ultimo = num.back();
    // Verifica se é dígito e se é par
    if (ultimo < '0' || ultimo > '9') return false;
    return ((ultimo - '0') % 2 == 0);
}

int main() {
    // Otimização para entrada/saída mais rápida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    // Tenta ler T, se falhar termina
    if (!(cin >> T)) return 0;
    
    // Consome o resto da linha após T (caso tenha caracteres extras)
    string linha;
    getline(cin, linha);

    while (T--) {
        string X, Y;
        // Lê X e Y, pulando espaços em branco
        cin >> X >> Y;

        // Validação extra
        if (X.empty() || Y.empty()) {
            cout << "NAO PARCEIROS" << "\n";
            continue;
        }

        // Verifica se ambos são pares
        if (isPar(X) && isPar(Y)) {
            cout << "PARCEIROS" << "\n";
        } else {
            cout << "NAO PARCEIROS" << "\n";
        }
    }
    return 0;
}