#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<pair<long long,int>> v(N), sorted_v;

    unordered_map<int, queue<long long>> cores;

    for(int i = 0; i < N; i++){
        cin >> v[i].first >> v[i].second;
        cores[v[i].second].push(v[i].first);
    }

    sorted_v = v;
    sort(sorted_v.begin(), sorted_v.end());

    for(auto [val, cor] : sorted_v){

        if(cores[cor].empty() || cores[cor].front() != val){
            cout << "NO\n";
            return 0;
        }

        cores[cor].pop();
    }

    cout << "YES\n";
}