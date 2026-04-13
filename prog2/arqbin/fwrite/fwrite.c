#include <stdio.h>


typedef struct {
    char nome[50];
    int dia,mes,ano;
}Contato;

void escrever(char arq []) {

    Contato c;
    FILE *file = fopen(arq,"ab");   //ab pois é o a(continua  escrevendo a partir doq ja ta escrito) + binario

    if (file) {

        printf("Digite um nome, o dia, o mês e o ano de nascimento:\n");
        scanf ("%49[^\n] %d%d%d", c.nome,&c.dia,&c.mes,&c.ano);
        fwrite(&c,sizeof(Contato),1,file);
        fclose(file);

    }
    else
        printf("Nao foi possivel concluir a solicitacao\n");

}



int main () {

    char arquivo [] = {"agenda.dat"};

    escrever(arquivo);

    return 0;
}