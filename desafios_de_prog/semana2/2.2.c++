#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    stack<int> st; // alturas de torres 'L' ainda não conectadas

    for (int i = 0; i < N; i++) {
        int h;
        char d;
        cin >> h >> d;

        // aceita '0' como 'O' (erro comum de digitação/fonte)
        if (d == '0') d = 'O';

        if (d == 'L') {
            // se está aninhando, altura nova deve ser estritamente menor
            if (!st.empty() && h >= st.top()) {
                cout << "N\n";
                return 0;
            }
            st.push(h);
        } else if (d == 'O') {
            // precisa fechar exatamente o topo
            if (st.empty() || st.top() != h) {
                cout << "N\n";
                return 0;
            }
            st.pop();
        } else {
            // caractere inválido
            cout << "N\n";
            return 0;
        }
    }

    cout << (st.empty() ? "S\n" : "N\n");
    return 0;
}