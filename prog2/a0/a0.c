#include <stdio.h>
#include <stdlib.h>

struct robo {
    int id;
    int ciclos;
    struct robo *prox;
};

struct lista {
    struct robo *inicio;
    int tam;
};

struct lista *cria_robo() { /*cria uma lista vazia para armazenar os robôs.*/

    struct lista *l;

    l = malloc(sizeof(struct lista));

    l->inicio = NULL;
    l->tam = 0;
    return l;

}

struct lista *insere_robo(struct lista *l, int id, int ciclos) { /*insere no final da lista*/

    struct robo *novo;
    novo = malloc(sizeof(struct robo));
        

    novo->id = id;
    novo->ciclos = ciclos;
    novo->prox = NULL;

    if (l->inicio == NULL) {
        l->inicio = novo;
    } else {
        struct robo *aux = l->inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    l->tam++;
    return l;

}

struct lista *remove_robo(struct lista *l, int id) {  /*se um robô tiver 0 ciclos restantes, ele deve ser removido da lista.*/

    struct robo *aux = l->inicio;
    struct robo *ant = NULL;

    while (aux != NULL) {
        if (aux->id == id) {
            if (ant == NULL) {
                l->inicio = aux->prox;
            } else {
                ant->prox = aux->prox;
            }
            free(aux);
            l->tam--;
            return l;
        }
        ant = aux;
        aux = aux->prox;
    }
    return l;

}

struct lista *executa_ciclo(struct lista *l) {   

    struct robo *aux = l->inicio;
    int num_ciclos = 0;

    while (aux != NULL && num_ciclos < 2) {

        if (aux->ciclos == 0) {
            l = remove_robo(l, aux->id);
        }

        aux->ciclos--;
        num_ciclos++;
        aux = aux->prox;

        if (l->tam == 0) {
            printf("Não há robôs na fila de recarga.\n");
            break;
        }

        if (aux->prox == NULL)  /* se chegar no final da lista, volta para o início*/
            break;

    }     
    return l;

}

struct lista *destroi_robo(struct lista *l) { /*libera toda a memória alocada para a lista e seus robôs.*/

    struct robo *aux = l->inicio;

    while (aux != NULL) {

        struct robo *temp = aux;
        aux = aux->prox;
        free(temp);

    }

    free(l);
    return NULL;

}

int main() {

    struct lista *l = cria_robo();
    int n;

    printf("Bem vindo ao rodizio de robos!\n");

    while (n != 3) {

        printf("Digite 1 para cadastrar um novo robo, 2 para executar um ciclo e 3 para encerrar o programa.\n");
        scanf("%d", &n);


        if (n == 1) {

            int id, ciclos;
            printf("Digite o ID do robo: ");
            scanf("%d", &id);
            printf("Digite o numero de ciclos do robo: ");
            scanf("%d", &ciclos);
            l = insere_robo(l, id, ciclos);

        } 
    
         else if (n == 2)
            l = executa_ciclo(l);
    }    

    if (n == 3) {
        printf("Encerrando o programa...\n");
        l = destroi_robo(l);
    }
    
    return 0;

}
