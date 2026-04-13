#include <stdio.h>


typedef struct {
    char nome[50];
    int dia,mes,ano;
}Contato;



void ler(char arq[]) {

    Contato c;
    FILE *file = fopen(arq,"rb");  //ler + binario

    if (file) {

        while(!feof(file)) {
            if(fread(&c,sizeof(Contato),1,file)) {   //enquanto tiver coisa p ler, precisa pq c n le um a mais
            printf("Nome: %s\nData: %d/%d/%d\n",c.nome,c.dia,c.mes,c.ano);
            }
        fclose(file);
        }
    }
    else 
        printf("Erro ao tentar ler o arquivo binario\n");

}


void escrever(char arq []) {

    Contato c;
    FILE *file = fopen(arq,"ab");   //ab pois é o a + binario

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
    ler(arquivo);

    return 0;
}