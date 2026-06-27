/*Um sistema gerencia tarefas com identificador, prioridade e tempo, armazenadas 
em uma lista duplamente encadeada ordenada por prioridade decrescente.
O programa deve oferecer: cadastro de tarefas (inserindo na ordem correta), execução/remoção da tarefa mais prioritária, 
ajuste de prioridades usando ponteiro de função (com opções linear +1, exponencial *2 ou personalizada), 
exibição da lista e encerramento com liberação de memória.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Tarefa {

    int id;
    int prioridade;
    int tempo;

    struct Tarefa *prox;
    struct Tarefa *ant;

} Tarefa;

typedef struct {

    Tarefa *inicio;
    int total;

} ListaTarefas;


ListaTarefas* criarLista() {

    ListaTarefas *l = (ListaTarefas*)malloc(sizeof(ListaTarefas));
    l->inicio = NULL;
    l->total = 0;

    return l;

}



void inserirTarefa(ListaTarefas *l, int id, int prioridade, int tempo) {

    struct Tarefa *nova = malloc(sizeof(struct Tarefa));

        nova->id = id;
        nova->prioridade = prioridade;
        nova->tempo = tempo;
        nova->prox = NULL;
        nova->ant = NULL;

        if (l->inicio == NULL) 
            l->inicio = nova;

        else {

            Tarefa *atual = l->inicio;
            while (atual != NULL && atual->prioridade >= prioridade) 
                atual = atual->prox;
            
            if (atual == NULL) {

                // Insere no final
                Tarefa *ultimo = l->inicio;
                while (ultimo->prox != NULL) 
                    ultimo = ultimo->prox;
                
                ultimo->prox = nova;
                nova->ant = ultimo;
            } else if (atual == l->inicio) {

                // Insere no início
                nova->prox = l->inicio;
                l->inicio->ant = nova;
                l->inicio = nova;

            } else {

                // Insere no meio
                nova->prox = atual;
                nova->ant = atual->ant;
                atual->ant->prox = nova;
                atual->ant = nova;

            }
        }

        l->total++;
}



void executarProxima(ListaTarefas *l) {

    struct Tarefa *atual = l->inicio;

    if (atual != NULL) {

        printf("Executando tarefa ID: %d, Prioridade: %d, Tempo: %d\n", atual->id, atual->prioridade, atual->tempo);

        l->inicio = atual->prox;

        if (l->inicio != NULL) 
            l->inicio->ant = NULL;
        
        free(atual);
        l->total--;

    } else {

        printf("Nenhuma tarefa para executar.\n");

    }

}



void ajustarPrioridades(ListaTarefas *l, int (*ajuste)(int)) {

    struct Tarefa *atual = l->inicio;

    while (atual != NULL) {

        atual->prioridade = ajuste(atual->prioridade);
        atual = atual->prox;

    }

    //Reordena a lista após o ajuste de prioridades
    ListaTarefas *novaLista = criarLista();
    atual = l->inicio;

    while (atual != NULL) {

        inserirTarefa(novaLista, atual->id, atual->prioridade, atual->tempo);
        atual = atual->prox;

    }

    //Libera a lista antiga
    free(l);

    //Atualiza a lista original para apontar para a nova lista
    l->inicio = novaLista->inicio;
    l->total = novaLista->total;
    free(novaLista);

}



void liberarLista(ListaTarefas *l) {

    Tarefa *atual = l->inicio;

    Tarefa *proximo;

    while (atual != NULL) {
        
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(l);
}



void exibirLista(ListaTarefas *l) {

    Tarefa *atual = l->inicio;

    if (atual == NULL) {

        printf("Lista de tarefas vazia.\n");
        return;

    }

    printf("Lista de tarefas:\n");

    while (atual != NULL) {

        printf("ID: %d, Prioridade: %d, Tempo: %d\n", atual->id, atual->prioridade, atual->tempo);
        atual = atual->prox;

    }

}


int linear(int p) {

    return p + 1;
}

int exponencial(int p) {

    return p * 2;
    
}

int personalizado(int p) {

    int valor;
    scanf("%d", &valor);
    return p + valor;

}


int main() {

    int opcao, id, prioridade, tempo;

    printf("Bem-vindo ao gerenciador de tarefas!\n");
    printf("Digite 0 para liberar lista e sair, 1 para cadastrar uma tarefa, 2 para executar a próxima, 3 para ajustar prioridades, 4 para exibir a lista e 5 para sair: ");

    scanf("%d", &opcao);


    ListaTarefas *lista = criarLista();

    while (opcao != 5) {

        switch (opcao) {

            case 0:
                printf("Encerrando o programa...\n");
                liberarLista(lista);
                return 0;

            case 1:
                printf("Digite o ID da tarefa: ");
                scanf("%d", &id);

                printf("Digite a prioridade da tarefa: ");
                scanf("%d", &prioridade);

                printf("Digite o tempo da tarefa: ");
                scanf("%d", &tempo);

                inserirTarefa(lista, id, prioridade, tempo);
                break;

            case 2:

                executarProxima(lista);
                break;

            case 3:

                printf("Escolha o tipo de ajuste de prioridade:\n");
                printf("1 - Linear (+1)\n");
                printf("2 - Exponencial (*2)\n");
                printf("3 - Personalizado\n");
                int tipo;
                scanf("%d", &tipo);

                if (tipo == 1) 
                    ajustarPrioridades(lista, linear);


                else if (tipo == 2) 
                    ajustarPrioridades(lista, exponencial);

                else if (tipo == 3) {

                    int valor;
                    printf("Digite o valor para somar na prioridade: ");
                    ajustarPrioridades(lista, personalizado);

                } else 
                    printf("Opção inválida.\n");
                
                break;

            case 4:

                exibirLista(lista);
                break;

            default:

                printf("Opção inválida.\n");
        }

        printf("\nDigite a próxima opção (0-4) ou 5 para sair: ");
        scanf("%d", &opcao);
    }
    return 0;
}
