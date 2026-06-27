#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    vector<int> bit;
    int n;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    int sum(int idx) {
        int r = 0;
        for (; idx > 0; idx -= idx & -idx)
            r += bit[idx];
        return r;
    }

    int rangeSum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

struct Query {
    int l, r, id;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> p(N + 1);
    vector<int> vals;

    for (int i = 1; i <= N; i++) {
        cin >> p[i];
        vals.push_back(p[i]);
    }

    sort(vals.begin(), vals.end());

    for (int i = 1; i <= N; i++) {
        p[i] = lower_bound(vals.begin(), vals.end(), p[i]) - vals.begin() + 1;
    }

    vector<Query> queries(Q);

    for (int i = 0; i < Q; i++) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    int block = sqrt(N);

    sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b) {
        int ba = a.l / block;
        int bb = b.l / block;

        if (ba != bb) return ba < bb;

        if (ba % 2 == 0)
            return a.r < b.r;
        else
            return a.r > b.r;
    });

    Fenwick fw(N);
    vector<long long> ans(Q);

    int L = 1, R = 0;
    long long inv = 0;
    int qtd = 0;

    auto countLess = [&](int x) {
        return fw.sum(x - 1);
    };

    auto countGreater = [&](int x) {
        return qtd - fw.sum(x);
    };

    auto addRight = [&](int x) {
        inv += countGreater(x);
        fw.add(x, 1);
        qtd++;
    };

    auto addLeft = [&](int x) {
        inv += countLess(x);
        fw.add(x, 1);
        qtd++;
    };

    auto removeRight = [&](int x) {
        inv -= countGreater(x);
        fw.add(x, -1);
        qtd--;
    };

    auto removeLeft = [&](int x) {
        inv -= countLess(x);
        fw.add(x, -1);
        qtd--;
    };

    for (auto q : queries) {
        while (R < q.r) addRight(p[++R]);
        while (R > q.r) removeRight(p[R--]);

        while (L < q.l) removeLeft(p[L++]);
        while (L > q.l) addLeft(p[--L]);

        ans[q.id] = inv;
    }

    for (int i = 0; i < Q; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}