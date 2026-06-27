#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    vector<int> S(K);
    for (int i = 0; i < K; i++) {
        cin >> S[i];
    }

    const int MAXH = 10000;

    vector<int> grundy(MAXH + 1, 0);

    for (int h = 1; h <= MAXH; h++) {
        vector<bool> seen(105, false);

        for (int s : S) {
            if (h >= s) {
                seen[grundy[h - s]] = true;
            }
        }

        int mex = 0;
        while (seen[mex]) mex++;

        grundy[h] = mex;
    }

    int M;
    cin >> M;

    while (M--) {
        int L;
        cin >> L;

        int xr = 0;

        for (int i = 0; i < L; i++) {
            int h;
            cin >> h;
            xr ^= grundy[h];
        }

        cout << (xr ? 'W' : 'L');
    }

    cout << '\n';

    return 0;
}