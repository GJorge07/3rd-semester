#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    string s;
    cin >> s;

    long long shift = 0;

    while (Q--) {
        int T;
        long long X;
        cin >> T >> X;

        if (T == 1) {
            shift = (shift + X) % N;
        } else {
            int idx = (X - 1 - shift % N + N) % N;
            cout << s[idx] << "\n";
        }
    }
}