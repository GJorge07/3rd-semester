#include <iostream>
#include <string>

using namespace std;

int main() {
    // Otimização para entrada/saída mais rápida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    
    while (T--) {
        string X, Y;
        cin >> X >> Y;

        // Verifica o último dígito de cada número
        int ultimoX = X.back() - '0';
        int ultimoY = Y.back() - '0';

        // Ambos devem ser pares
        if (ultimoX % 2 == 0 && ultimoY % 2 == 0) {
            cout << "PARCEIROS\n";
        } else {
            cout << "NAO PARCEIROS\n";
        }
    }
    return 0;
}