#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> S(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    unordered_map<int, int> left_count;

    // Lado esquerdo: a*b + c
    for (int a : S) {
        for (int b : S) {
            for (int c : S) {
                int val = a * b + c;
                left_count[val]++;
            }
        }
    }

    long long result = 0;

    // Lado direito: d*(e + f), d != 0
    for (int d : S) {
        if (d == 0) continue;

        for (int e : S) {
            for (int f : S) {
                int val = d * (e + f);

                if (left_count.count(val)) {
                    result += left_count[val];
                }
            }
        }
    }

    cout << result << "\n";
}