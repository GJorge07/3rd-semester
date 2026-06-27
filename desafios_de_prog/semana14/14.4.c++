#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estrutura do nó da Treap
struct Node {
    int val;
    int prior;
    int size;
    Node *l, *r;
    
    Node(int v) : val(v), prior(rand()), size(1), l(nullptr), r(nullptr) {}
};

typedef Node* pnode;

// Retorna o tamanho da subárvore com segurança contra ponteiros nulos
int sz(pnode t) {
    return t ? t->size : 0;
}

// Atualiza o tamanho do nó com base nos seus filhos
void upd_sz(pnode t) {
    if (t) t->size = sz(t->l) + 1 + sz(t->r);
}

// Divide a árvore em duas (l e r) com base em uma posição (índice) implicitamente calculada
void split(pnode t, pnode &l, pnode &r, int key, int add = 0) {
    if (!t) {
        l = r = nullptr;
        return;
    }
    int cur_key = add + sz(t->l); // Índice implícito do nó atual
    if (cur_key >= key) {
        split(t->l, l, t->l, key, add);
        r = t;
    } else {
        split(t->r, t->r, r, key, cur_key + 1);
        l = t;
    }
    upd_sz(t);
}

// Une duas subárvores l e r em uma única árvore t
void merge(pnode &t, pnode l, pnode r) {
    if (!l || !r) {
        t = l ? l : r;
        return;
    }
    if (l->prior > r->prior) {
        merge(l->r, l->r, r);
        t = l;
    } else {
        merge(r->l, l, r->l);
        t = r;
    }
    upd_sz(t);
}

// Insere um valor em uma posição específica em O(log N)
void insert(pnode &t, int pos, int val) {
    pnode l, r;
    split(t, l, r, pos);
    pnode new_node = new Node(val);
    merge(l, l, new_node);
    merge(t, l, r);
}

// Remove um valor de uma posição específica em O(log N)
void erase(pnode &t, int pos) {
    pnode l, mid, r;
    split(t, l, r, pos);
    split(r, mid, r, 1); // Separa o elemento da posição atual
    delete mid;          // Libera a memória
    merge(t, l, r);
}

// Consulta o valor em uma posição específica em O(log N)
int query(pnode t, int pos, int add = 0) {
    int cur_key = add + sz(t->l);
    if (cur_key == pos) return t->val;
    if (cur_key > pos) return query(t->l, pos, add);
    return query(t->r, pos, cur_key + 1);
}

int main() {
    // Otimização extrema de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Seed para garantir o balanceamento aleatório da Treap
    srand(1337);

    int N, Q;
    if (!(cin >> N >> Q)) return 0;

    pnode root = nullptr;
    for (int i = 0; i < N; ++i) {
        int item;
        cin >> item;
        // Construção inicial na Treap
        insert(root, i, item);
    }

    int camera_pos = 0;

    for (int q = 0; q < Q; ++q) {
        char op;
        cin >> op;

        if (op == 'm') {
            int D;
            cin >> D;
            camera_pos += D; // O(1)
        } 
        else if (op == 'i') {
            int T;
            cin >> T;
            insert(root, camera_pos, T); // O(log N) estrito
        } 
        else if (op == 'd') {
            erase(root, camera_pos); // O(log N) estrito
        } 
        else if (op == 'q') {
            cout << query(root, camera_pos) << "\n"; // O(log N) estrito
        }
    }

    return 0;
}