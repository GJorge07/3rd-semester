#include <stdio.h>
#include <stdlib.h>


typedef struct no {

    int valor,altura;
    struct no *esq, *dir, *pai;

}NoAvl;


NoAvl *novono (int x) {                        //cria um novo nó

    NoAvl *no = malloc(sizeof(NoAvl));

    if (no) {

        no->altura = 0;
        no->esq = NULL;
        no->dir = NULL;
        no->pai = NULL;
        no->valor = x;

    }

    return no;
}

int maior (int a, int b) {             //descobre qual subarvore tem maior altura
    return (a > b)? a:b;
}


int altura (NoAvl *no) {               //retorna a altura de um nó

    if (no == NULL)
        return -1;

    return no->altura;
    
}



int fb(NoAvl *no) {                      //calcula o fator de balanceamento

    if (no)
        return (altura(no->esq) - altura(no->dir));
    return 0;

}


NoAvl *rotacaoesq(NoAvl *raiz) {        //quando ta desbalanceada pra direita (-2,-3...)

    NoAvl *y = raiz->dir;               //raiz aponta pro seu filho a dir
    NoAvl *f = y->esq;                  //possivel filho

    y->esq = raiz;                      //antiga raiz desce
    raiz->dir = f;                      //se tiver filho, ele vai pra dir

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
    y->altura = maior(altura(y->esq),altura(y->dir));

    return y;           //é a nova raiz
}


NoAvl *rotacaodir(NoAvl *raiz) {

    NoAvl *y = raiz->esq;
    NoAvl *f = y->dir;

    y->dir = raiz;
    raiz->esq = f;

    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
    y->altura = maior(altura(y->esq),altura(y->dir));

    return y;           //é a nova raiz

}


NoAvl *rotacaodiresq(NoAvl *raiz) {

    raiz->dir = rotacaodir(raiz->dir);     //faz rotação dir do raiz->dir e dps rotaciona td pra esq
    
    return rotacaoesq(raiz);
}

NoAvl *rotacaoesqdir(NoAvl *raiz) {

    raiz->esq = rotacaoesq(raiz->esq);

    return rotacaodir(raiz);
}


NoAvl *balancear(NoAvl *raiz) {              //se vira p entender, só raciocinar
 
    int f_balanc = fb(raiz);

    if(f_balanc < -1 && fb(raiz->dir) <= 0)         
        raiz = rotacaoesq(raiz);

    else if(f_balanc < -1 && fb(raiz->dir) > 0)
        raiz = rotacaodiresq(raiz);

    else if(f_balanc > 1 && fb(raiz->esq) >= 0)
        raiz = rotacaodir(raiz);
    
    else if(f_balanc > 1 && fb(raiz->esq) < 0)
        raiz = rotacaoesqdir(raiz);

    return raiz;
}




NoAvl *inserir(NoAvl *raiz, int num){

    // se a árvore (ou subárvore) está vazia, cria novo nó
    if(raiz == NULL) 
        return novono(num);
    
    else { 
    // menores vão pra esquerda, maiores pra direita
    if(num < raiz->valor)
        raiz->esq = inserir(raiz->esq, num);
    else
        raiz->dir = inserir(raiz->dir, num);
    }

    raiz->altura = maior(altura(raiz->esq),altura(raiz->dir)) +1;   //+1 pq o nó atual conta como um nível
    raiz = balancear(raiz);
    // retorna a raiz (importante pra recursão)
    return raiz;
}    

NoAvl *remover(NoAvl *raiz, int num){

    // se a árvore está vazia
    if(raiz == NULL) 
        return NULL;
    
    else {
        // procura o nó
        if(num < raiz->valor)
            raiz->esq = remover(raiz->esq, num);
        else if(num > raiz->valor)
            raiz->dir = remover(raiz->dir, num);
        
        else {  // achou quem precisa remover!
            
            // CASO 1: nó folha
            if(raiz->esq == NULL && raiz->dir == NULL) {
                free(raiz);
                return NULL;
            }
            
            // CASO 2: um filho (esquerda)
            else if(raiz->esq == NULL) {
                NoAvl *temp = raiz->dir;
                free(raiz);
                return temp;
            }
            
            // CASO 2: um filho (direita)
            else if(raiz->dir == NULL) {
                NoAvl *temp = raiz->esq;
                free(raiz);
                return temp;
            }
            
            // CASO 3: dois filhos
            else {
                // pega o sucessor (menor da direita)
                NoAvl *sucessor = raiz->dir;
                while(sucessor->esq != NULL)
                    sucessor = sucessor->esq;
                
                raiz->valor = sucessor->valor;
                raiz->dir = remover(raiz->dir, sucessor->valor);
            }
        }
    }
    
    // AQUI É IGUAL AO INSERIR
    raiz->altura = maior(altura(raiz->esq), altura(raiz->dir)) + 1;
    raiz = balancear(raiz);
    
    return raiz;
}


void imprimir (NoAvl *raiz, int nivel) {   //n entendi nd
    int i;

    if (raiz) {

        imprimir(raiz->dir, nivel+1);
        printf("\n\n");

        for (int i = 0; i < nivel; i++) 
            printf("\t");

        printf("%d",raiz->valor);
        imprimir(raiz->esq,nivel+1);

    }

}