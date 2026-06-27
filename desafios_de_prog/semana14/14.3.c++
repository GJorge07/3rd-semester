#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    int B = sqrt(N) + 1;

    vector<long long> ans(N + 2, 0);

    vector<vector<long long>> diff(B + 1, vector<long long>(N + B + 5, 0));

    for (int i = 0; i < K; i++) {
        int A, L, D;
        cin >> A >> L >> D;

        if (D <= B) {
            int fim = A + (L - 1) * D;

            diff[D][A] += 1;
            diff[D][fim + D] -= 1;
        } else {
            for (int j = 0; j < L; j++) {
                ans[A + j * D]++;
            }
        }
    }

    for (int d = 1; d <= B; d++) {
        for (int i = 1; i <= N; i++) {
            diff[d][i] += diff[d][i - d >= 1 ? i - d : 0];
            ans[i] += diff[d][i];
        }
    }

    for (int i = 1; i <= N; i++) {
        if (i > 1) cout << ' ';
        cout << ans[i];
    }

    cout << '\n';

    return 0;
}