#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string s;
    cin >> s;

    vector<int> freq(26, 0);

    for (char c : s)
        freq[c - 'A']++;

    int odd = 0;
    char middle = 0;

    for (int i = 0; i < 26; i++) {
        if (freq[i] % 2 != 0) {
            odd++;
            middle = 'A' + i;
        }
    }

    if (odd > 1) {
        cout << "NO SOLUTION";
        return 0;
    }

    string left = "";

    for (int i = 0; i < 26; i++) {
        left.append(freq[i] / 2, 'A' + i);
    }

    string right = left;
    reverse(right.begin(), right.end());

    cout << left;

    if (middle)
        cout << string(freq[middle - 'A'] % 2, middle);

    cout << right;

    return 0;
}