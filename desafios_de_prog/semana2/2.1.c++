#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    queue<int> q;
    stack<int> st;
    priority_queue<int> pq;

    bool fifo = true;
    bool lifo = true;
    bool priority = true;

    for (int i = 0; i < N; i++) {
        int type, x;
        cin >> type >> x;

        if (type == 0) { // entrada
            q.push(x);
            st.push(x);
            pq.push(x);
        }
        else { // saída

            if (fifo) {
                if (q.empty() || q.front() != x)
                    fifo = false;
                else
                    q.pop();
            }

            if (lifo) {
                if (st.empty() || st.top() != x)
                    lifo = false;
                else
                    st.pop();
            }

            if (priority) {
                if (pq.empty() || pq.top() != x)
                    priority = false;
                else
                    pq.pop();
            }
        }
    }

    int count = fifo + lifo + priority;

    if (count == 0) cout << "unknown\n";
    else if (count > 1) cout << "ambiguous\n";
    else if (fifo) cout << "fifo\n";
    else if (lifo) cout << "lifo\n";
    else cout << "priority\n";

    return 0;
}