#include <bits/stdc++.h>
using namespace std;

long long calc(long long a, long long b, long long c, char op1, char op2) {
    if (op1 == '*') {
        long long t = a * b;
        if (op2 == '+') return t + c;
        if (op2 == '-') return t - c;
        return t * c;
    }
    if (op2 == '*') {
        long long t = b * c;
        if (op1 == '+') return a + t;
        if (op1 == '-') return a - t;
        return a * t;
    }
    if (op1 == '+') {
        if (op2 == '+') return a + b + c;
        if (op2 == '-') return a + b - c;
    }
    if (op1 == '-') {
        if (op2 == '+') return a - b + c;
        if (op2 == '-') return a - b - c;
    }
    return 0;
}

int main() {
    int A, B, C;
    cin >> A >> B >> C;

    vector<int> v = {A, B, C};
    vector<char> ops = {'+', '-', '*'};

    long long ans = LLONG_MAX;

    sort(v.begin(), v.end());

    do {
        for (char op1 : ops) {
            for (char op2 : ops) {
                ans = min(ans, calc(v[0], v[1], v[2], op1, op2));
            }
        }
    } while (next_permutation(v.begin(), v.end()));

    cout << ans << "\n";
}