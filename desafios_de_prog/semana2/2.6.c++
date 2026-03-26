#include <bits/stdc++.h>
using namespace std;

struct Node{
    long long val;
    long long cnt;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    deque<Node> L, R;

    while(N--){

        char op;
        cin >> op;

        if(op=='i'){
            long long q, t;
            cin >> q >> t;

            // insere na posição atual (frente de R)
            if(!R.empty() && R.front().val == t)
                R.front().cnt += q;
            else
                R.push_front({t, q});
        }

        else if(op=='m'){
            int d;
            cin >> d;

            while(d > 0){
                // move frente de R para trás de L
                auto& cur = R.front();
                if(!L.empty() && L.back().val == cur.val){
                    L.back().cnt += 1;
                } else {
                    L.push_back({cur.val, 1});
                }
                cur.cnt--;
                if(cur.cnt == 0) R.pop_front();
                d--;
            }

            while(d < 0){
                // move trás de L para frente de R
                auto& cur = L.back();
                if(!R.empty() && R.front().val == cur.val){
                    R.front().cnt += 1;
                } else {
                    R.push_front({cur.val, 1});
                }
                cur.cnt--;
                if(cur.cnt == 0) L.pop_back();
                d++;
            }
        }

        else if(op=='d'){
            auto& cur = R.front();
            cur.cnt--;
            if(cur.cnt == 0) R.pop_front();
        }

        else if(op=='q'){
            cout << R.front().val << "\n";
        }
    }
}