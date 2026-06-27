#include <stdio.h>
#include <stdlib.h>


#define MAX(a,b) ((a)>(b)?(a):(b))
#define FB(a) ((a == NULL) ? 0 : (a)->fb) /*FB ∈ [-2, +2] durante o processo de balanceamento*/


typedef struct {
    int chave;
    int fb;
    no *pai;
    no *esq;
    no *dir;
} no;


typedef struct {
    no *raiz;
} arvore;


no* tree_insert(arvore *t, no *z) {
    no *x, *y;

    x = t->raiz;
    y = NULL;
    while(x != NULL) {
        y = x;
        if(z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;
    if(y == NULL)
        t->raiz = z;
    else if(z->chave < y->chave)
        y->esq = z;
    else
        y->dir = z;
    return y;
}


void transplant(arvore *t, no *u, no *v) {
    if(u->pai == NULL)
        t->raiz = v;
    else if(u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;
    if(v != NULL)
        v->pai = u->pai;
}


no* tree_minimum(no *x) {
    while(x->esq != NULL)
        x = x->esq;
    return x;
}


no* tree_delete(arvore *t, no *z) {
    no *x, *y;

    x = z->pai;
    if(z->esq == NULL)
        transplant(t, z, z->dir);
    else if(z->dir == NULL)
        transplant(t, z, z->esq);
    else {
        y = tree_minimum(z->dir);
        x = y->pai;
        if(y != z->dir) {
            transplant(t, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        transplant(t, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
    }
    return x;
}


no* rot_esq(no *p) {
    no *q;

    q = p->dir;
    p->dir = q->esq;
    if(p->dir)
        p->dir->pai = p;
    q->esq = p;
    q->pai = p->pai;
    p->pai = q;    
    
    if (q->fb == -1) {
        p->fb = 0;
        q->fb = 0;
    }
    else if (q->fb == 0) {
        p->fb = -1;
        q->fb = 1;
    }


    return q;
}


no* rot_dir(no *p) {
    no *q;

    q = p->esq;
    p->esq = q->dir;
    if(p->esq)
        p->esq->pai = p;
    q->dir = p;
    q->pai = p->pai;
    p->pai = q;   

    if (q->fb == 1) {
        p->fb = 0;
        q->fb = 0;
    }
    else if (q->fb == 0) {
        p->fb = 1;
        q->fb = -1;
    }

    return q;
}


no* rot_esqdir(no *p) {
    p->esq = rot_esq(p->esq);
    p->esq->pai = p;
    return rot_dir(p);
}


no* rot_diresq(no *p) {
    p->dir = rot_dir(p->dir);
    p->dir->pai = p;
    return rot_esq(p);
}


no* rot_esqdir(no *p) {
    no *q, *r;
    int fb_r;

    q = p->esq;
    r = q->dir;
    fb_r = r->fb;

    p->esq = r->dir;
    if(p->esq)
        p->esq->pai = p;
    q->dir = r->esq;
    if(q->dir)
        q->dir->pai = q;
    r->esq = q;
    r->dir = p;
    r->pai = p->pai;
    p->pai = r;
    q->pai = r;


    if(fb_r == 1) {
        p->fb = -1;
        q->fb = 0;
    }
    else if(fb_r == -1) {
        p->fb = 0;
        q->fb = 1;
    }
    else {
        p->fb = 0;
        q->fb = 0;
    }

    r->fb = 0;


    return r;
}


no* rot_diresq(no *p) {
    no *q, *r;
    int fb_r;

    q = p->dir;
    r = q->esq;
    fb_r = r->fb;

    p->dir = r->esq;
    if(p->dir)
        p->dir->pai = p;
    q->esq = r->dir;
    if(q->esq)
        q->esq->pai = q;
    r->dir = q;
    r->esq = p;
    r->pai = p->pai;
    p->pai = r;
    q->pai = r;

    if(fb_r == -1) {
        p->fb = 1;
        q->fb = 0;
    }
    else if(fb_r == 1) {
        p->fb = 0;
        q->fb = -1;
    }
    else {
        p->fb = 0;
        q->fb = 0;
    }

    r->fb = 0;

    return r;
}


no* avl_balance(no *x) {
    int fb;
    no *y;

    y = x;
    fb = x->fb;

    if(fb > 1)
        if(x->esq->fb < 0)
            y = rot_esqdir(x);
        else
            y = rot_dir(x);

    else if(fb < -1)
        if(x->dir->fb > 0)
            y = rot_diresq(x);
        else
            y = rot_esq(x);

    return y;
}


void troca_filho(arvore *t, no *u, no *v) {
    if(v->pai == NULL)
        t->raiz = v;
    else if(u == v->pai->esq)
        v->pai->esq = v;
    else
        v->pai->dir = v;
}


void avl_insert(arvore *t, no *z) {
    no *x, *y;
    no *filho;

    z->fb = 0;
    z->esq = NULL;
    z->dir = NULL;

    x = tree_insert(t, z);
    filho = z;

    while(x != NULL) {
        if(filho == x->esq)
            x->fb++;    /*quando cresce à esquerda*/
        else
            x->fb--;    /*quando cresce à direita*/

        if(x->fb == 0)
            break;

        if(x->fb == 2 || x->fb == -2) {
            y = avl_balance(x);
            troca_filho(t, x, y);
            break;
        }

        filho = x;
        x = x->pai;
    }
}


void avl_delete(arvore *t, no *z) {
    no *x, *y, *filho_removido;

    filho_removido = z;
    x = tree_delete(t, z);

    while(x != NULL) {

        if(filho_removido == x->esq)
            x->fb--;   
        else
            x->fb++;   

        if(x->fb == 1 || x->fb == -1)
            break;    

        if(x->fb == 2 || x->fb == -2) {
            y = avl_balance(x);
            troca_filho(t, x, y);

            if(y->fb != 0)
                break;

            x = y;
        }

        filho_removido = x;
        x = x->pai;
    }
}
    