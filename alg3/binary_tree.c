#include <stdio.h>
#include <stdlib.h>

// ================== ESTRUTURA ==================
// Cada nó tem:
// - valor
// - ponteiro para esquerda
// - ponteiro para direita
typedef struct no {
    int valor;
    struct no *esq, *dir, *pai;
} Noarv;

Noarv *raiz;
// ================== INSERÇÃO ==================
Noarv *inserir(Noarv *raiz, int num){

    // se a árvore (ou subárvore) está vazia, cria novo nó
    if(raiz == NULL) {

        Noarv *novo = malloc(sizeof(Noarv));
        novo->valor = num;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo; // retorna o novo nó

    }

    // menores vão pra esquerda, maiores pra direita
    if(num < raiz->valor)
        raiz->esq = inserir(raiz->esq, num);
    else
        raiz->dir = inserir(raiz->dir, num);

    // retorna a raiz (importante pra recursão)
    return raiz;
}

Noarv* inserir_iterativo(Noarv *raiz, int valor){

    // cria o novo nó
    Noarv *novo = malloc(sizeof(Noarv));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;

    // se a árvore estiver vazia
    if(raiz == NULL)
        return novo;

    Noarv *atual = raiz;
    Noarv *pai = NULL;

    // percorre a árvore
    while(atual != NULL){
        pai = atual;

        if(valor < atual->valor)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    // conecta o novo nó no pai
    if(valor < pai->valor)
        pai->esq = novo;
    else
        pai->dir = novo;

    return raiz;
}


// ================== BUSCA ==================
Noarv *busca_recursiva(Noarv *raiz, int valor){

    // se chegou em NULL ou achou o valor
    if(raiz == NULL || raiz->valor == valor)
        return raiz;

    // decide pra qual lado ir
    if(valor < raiz->valor)
        return busca_recursiva(raiz->esq, valor);
    else
        return busca_recursiva(raiz->dir, valor);
}


Noarv *busca_iterativa(Noarv *raiz, int valor) {

    while (raiz) {

        if (valor < raiz->valor)
            raiz = raiz->esq;
        else if (valor > raiz->valor)
            raiz = raiz->dir;
        else
            return raiz;   //quando valor == raiz
    }
    return NULL;        //se o elemento não estiver na AB

}
// ================== MÍNIMO ==================
Noarv *minimo(Noarv *raiz){

    if(raiz == NULL) 
        return NULL;

    // vai sempre pra esquerda até o final
    while(raiz->esq != NULL)
        raiz = raiz->esq;

    return raiz;
}

Noarv *minimorec(Noarv *raiz){

    if(raiz == NULL) 
        return NULL;

    // se não tem filho esquerdo, achou o mínimo
    if(raiz->esq == NULL)
        return raiz;
    
    // senão, continua procurando na esquerda
    return minimorec(raiz->esq);
}


// ================== MÁXIMO ==================
Noarv *maximo(Noarv *raiz){

    if(raiz == NULL) 
        return NULL;

    // vai sempre pra direita até o final
    while(raiz->dir != NULL)
        raiz = raiz->dir;

    return raiz;
}


// ================== SUCESSOR ==================
Noarv *sucessor(Noarv *raiz, Noarv *x){

    // caso 1: tem subárvore à direita
    // sucessor = menor da direita
    if(x->dir != NULL)
        return minimo(x->dir);

    // caso 2: não tem direita → subir na árvore (sai da raiz e vai comparando com o valor até achar o menor numero maior que ele)
    Noarv *succ = NULL; 

    while(raiz != NULL){

        if(x->valor < raiz->valor){
            succ = raiz;       // candidato a sucessor
            raiz = raiz->esq;
        }
        else
            raiz = raiz->dir;
    }

    return succ;
}


// ================== ANTECESSOR ==================
Noarv *antecessor(Noarv *raiz, Noarv *x){

    // caso 1: tem subárvore à esquerda
    // antecessor = maior da esquerda
    if(x->esq != NULL)
        return maximo(x->esq);

    // caso 2: subir na árvore
    Noarv *ant = NULL;

    while(raiz != NULL){

        if(x->valor > raiz->valor){
            ant = raiz;        // possível antecessor
            raiz = raiz->dir;
        }
        else{
            raiz = raiz->esq;
        }
    }

    return ant;
}

// ================== ALTURA ======================

int altura (Noarv *raiz) {

    if (raiz == NULL)
        return -1;
    
    if (altura(raiz->esq) > altura(raiz->dir))
        return altura(raiz->esq) + 1;
    else
        return altura(raiz->dir) + 1;

}

//=================== CONTA NOS =====================
int contaNodo( Noarv *raiz ){

  if( raiz == NULL ) 
        return 0;

  return contaNodo( raiz->esq ) + contaNodo( raiz->dir ) + 1; //conta tudo da esq + conta td da dir + conta raiz principal

}



// ================== IMPRESSÕES ==================

// PRE-ORDEM: raiz → esquerda → direita
void imprimir_v1(Noarv *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->valor);
        imprimir_v1(raiz->esq);
        imprimir_v1(raiz->dir);
    }
}

// EM ORDEM: esquerda → raiz → direita
void imprimir_v2(Noarv *raiz){
    if(raiz != NULL){
        imprimir_v2(raiz->esq);
        printf("%d ", raiz->valor);
        imprimir_v2(raiz->dir);
    }
}

// PÓS-ORDEM: esquerda → direita → raiz
void imprimir_v3(Noarv *raiz){
    if(raiz != NULL){
        imprimir_v3(raiz->esq);
        imprimir_v3(raiz->dir);
        printf("%d ", raiz->valor);
    }
}


// ================== REMOÇÃO ==================
Noarv *remover(Noarv *raiz, int valor){

    if(raiz == NULL)
        return NULL;

    // procura o nó
    if(valor < raiz->valor)
        raiz->esq = remover(raiz->esq, valor);

    else if(valor > raiz->valor)
        raiz->dir = remover(raiz->dir, valor);

    else {        //quando vc acha quem vc vai remover

        // ===== CASO 1: nó folha =====
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }

        // ===== CASO 2: um filho =====
        else if(raiz->esq == NULL){
            Noarv *temp = raiz->dir;
            free(raiz);
            return temp;
        }

        else if(raiz->dir == NULL){
            Noarv *temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // ===== CASO 3: dois filhos =====
        else{
            // pega o sucessor (menor da direita)
            Noarv *temp = minimo(raiz->dir);

            // copia o valor do sucessor pra onde tá a raiz
            raiz->valor = temp->valor;

            // remove o sucessor lá debaixo, agr ele só fica onde antes era a raiz
            raiz->dir = remover(raiz->dir, temp->valor);
        } 
    }

    return raiz;
}

void transplante(Noarv *u, Noarv *v){

    // se u é a raiz
    if(u->pai == NULL)
        raiz = v;

    // se u é filho esquerdo
    else if (u == u->pai->esq)
        u->pai->esq = v;


    // se é filho direito
    else
        u->pai->dir = v;

    // ajusta pai de v
    if(v != NULL)
        v->pai = u->pai;
}

void remover_v2(Noarv *z){

    // caso 1: sem filho esquerdo
    if(z->esq == NULL)
        transplante( z, z->dir);
    

    // caso 2: sem filho direito
    else if(z->dir == NULL)
        transplante(z, z->esq);


    // caso 3: dois filhos
    else{
        Noarv *y = minimo(z->dir); // sucessor

        // se y não é filho direto
        if(y->pai != z){

            transplante(y, y->dir);

            y->dir = z->dir;
            y->dir->pai = y;
        }

        transplante(z, y);

        y->esq = z->esq;
        y->esq->pai = y;
    }

    free(z);
}


int somaarv(Noarv *raiz) {

    if (!raiz)
        return 0;

   return raiz->valor +  somaarv(raiz->esq) + somaarv(raiz->dir);

}

//Dobrar a quantidade de nodos da ´arvore criando para cada um novo pai que tem a chave determinada da seguinte forma:
//• se o nodo n tiver chave k que ´e par, seu pai ´e um novo nodo que cont´em chave k + 1 e n ´e ser´a seufilho esquerdo;
//• se o nodo n tiver chave k que ´e ´ımpar, seu pai ´e um novo nodo que cont´em chave k − 1 e n ´e ser´a seu filho direito.
Noarv *dobraarv(Noarv *raiz) {

if (raiz == NULL)
    return NULL;

raiz->esq = dobraarv(raiz->esq);        //pega o ultimo filho da esq
raiz->dir = dobraarv(raiz->dir);        //pega o ultimo filho da dir


Noarv *novopai = malloc(sizeof(Noarv));

if (raiz->valor % 2 == 0) {
    novopai->valor = raiz->valor + 1;
    novopai->esq = raiz;
    novopai->dir = NULL;
}
else {
    novopai->valor = raiz->valor - 1;
    novopai->dir = raiz;
    novopai->esq = NULL;
}

    return novopai;

}


Noarv *maiornaraiz(Noarv *raiz) {

    int maior = 0;
    Noarv *aux,*temp = raiz;
    if (raiz) {
        while (raiz->dir != NULL) {
            raiz = raiz->dir;
            if (raiz->valor > maior)
                maior = raiz->valor;
        }
    }
    aux = temp;
    temp = raiz;
    raiz = aux;


}

Noarv *excluichave (Noarv *raiz, int valor) {

    if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
    }


    else if (raiz->esq == NULL) {
        Noarv *temp = raiz->dir;
        free(raiz);
        return temp;
    }

    else if (raiz->dir == NULL) {
        Noarv *temp = raiz->esq;
        free(raiz);
        return temp;
    }

    else {

        Noarv *temp = maximo(raiz->esq);

        raiz->valor = temp->valor;

        raiz->dir = excluichave(raiz->esq,temp->valor);

    }
    return excluichave(raiz, valor); //continua excluindo duplicatas
}



Noarv  *buscapreorder(Noarv *raiz, int valor) {

        if (raiz == NULL) 
            return NULL;

        if (raiz->valor == valor) 
            return raiz;
        
        Noarv *temp = buscapreorder(raiz->esq,valor);
        if (temp != NULL)
            return temp;

        return buscapreorder(raiz->dir,valor);
}



int contafilhos(Noarv *raiz) {

    if (raiz == NULL)
        return 0;

    int esq = contafilhos(raiz->esq);
    int dir = contafilhos(raiz->dir);

    int soma = esq + dir;

    return soma + 1;
}   //ai na chamada faz contafilhos(raiz) - 1 pra contar filhos, pq aq da a qntdd total


int ehavl(Noarv *raiz) {

    if (raiz == NULL)
        return 1;

    int esq = altura(raiz->esq);
    int dir = altura(raiz->dir);

    int fb = esq - dir;

    if (fb < -1 || fb > 1)
        return 0;

    return ehavl(raiz->esq) && ehavl(raiz->dir);
}

no* inserirComVizinhos(no* raiz, no* X) {
    // 1. Se a árvore estiver vazia, o X vira a própria raiz
    if (raiz == NULL) {
        X->esq = X->dir = X->ant = X->suc = NULL;
        return X; 
    }

    no* atual = raiz;
    no* pai = NULL;
    no* candidatoAnt = NULL;
    no* candidatoSuc = NULL;

    // 2. Busca iterativa pela posição
    while (atual != NULL) {
        pai = atual;
        if (X->chave < atual->chave) {
            candidatoSuc = atual; // Caminho para esquerda -> sucessor
            atual = atual->esq;
        } else {
            candidatoAnt = atual; // Caminho para direita -> antecessor
            atual = atual->dir;
        }
    }

    // 3. Conecta o X ao pai
    if (X->chave < pai->chave) 
        pai->esq = X;
    else 
        pai->dir = X;

    // 4. Ajusta a "corrente" (antecessor e sucessor)
    X->ant = candidatoAnt;
    X->suc = candidatoSuc;

    if (candidatoAnt != NULL) candidatoAnt->suc = X;
    if (candidatoSuc != NULL) candidatoSuc->ant = X;

    X->esq = X->dir = NULL;

    // 5. Retorna a raiz original (ou a nova, se fosse o primeiro nó)
    return raiz;
}


// Função para retornar o maior entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para retornar o menor entre dois números
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Calcula o caminho mais longo da raiz até uma folha (Altura)
int alturaMaxima(no* p) {
    if (p == NULL) return 0;
    return 1 + max(alturaMaxima(p->esq), alturaMaxima(p->dir));
}

// Calcula o caminho mais curto da raiz até uma folha
int alturaMinima(no* p) {
    if (p == NULL) return 0;
    
    // Se for um nó folha
    if (p->esq == NULL && p->dir == NULL) return 1;

    // Se só tiver o filho da direita, o caminho curto TEM que ir por ali
    if (p->esq == NULL) return 1 + alturaMinima(p->dir);
    
    // Se só tiver o filho da esquerda, o caminho curto TEM que ir por ali
    if (p->dir == NULL) return 1 + alturaMinima(p->esq);

    // Se tiver os dois, pega o menor dos dois caminhos
    return 1 + min(alturaMinima(p->esq), alturaMinima(p->dir));
}

// Função principal que resolve a questão
int verificaEquilibrioRamos(no* raiz) {
    if (raiz == NULL) return 1; // Árvore vazia é considerada equilibrada

    int maior = alturaMaxima(raiz);
    int menor = alturaMinima(raiz);

    // Verifica se a diferença é no máximo 1
    if ((maior - menor) <= 1) {
        return 1; // Sucesso
    } else {
        return 0; // Falhou
    }
}

// ================== MENU ==================
void menu(){
    printf("\n1 - Inserir");
    printf("\n2 - Remover");
    printf("\n3 - Buscar");
    printf("\n4 - Pre-ordem");
    printf("\n5 - Em ordem");
    printf("\n6 - Pos-ordem");
    printf("\n7 - Minimo");
    printf("\n8 - Maximo");
    printf("\n9 - Sucessor");
    printf("\n10 - Antecessor");
    printf("\n0 - Sair\n");
}


// ================== MAIN ==================
int main(){

    Noarv *raiz = NULL;
    int opcao, valor;

    do{
        menu();
        scanf("%d", &opcao);

        switch(opcao){

        case 1:
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            break;

        case 2:
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;

        case 3:{
            scanf("%d", &valor);
            Noarv *res = busca_recursiva(raiz, valor);
            if(res) printf("Encontrado\n");
            else printf("Nao encontrado\n");
            break;
        }

        case 4:
            imprimir_v1(raiz);
            printf("\n");
            break;

        case 5:
            imprimir_v2(raiz);
            printf("\n");
            break;

        case 6:
            imprimir_v3(raiz);
            printf("\n");
            break;

        case 0:
            printf("Saindo...\n");
            break;
        }

    }while(opcao != 0);

    return 0;
}




Noarv *antecessor(Noarv *raiz, Noarv *x) {

    if (x) {

        if (x->esq != NULL)
            return maximo(x->esq);

        Noarv *ant = NULL;

        while (raiz != NULL) {
            if (raiz->valor < x->valor) {
                ant = raiz;
                raiz = raiz->dir;
            }
            else
                raiz = raiz->esq;
        }
    }
    return ant;
}