#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    long long moves = 0;
    long long prev, x;

    cin >> prev;

    for (int i = 1; i < n; i++) {
        cin >> x;

        if (x < prev) {
            moves += prev - x;
        } else {
            prev = x;
        }
    }

    cout << moves << "\n";

    return 0;
}