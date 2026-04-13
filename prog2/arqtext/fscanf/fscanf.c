#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void escrever(char f[]) {

    FILE *file = fopen(f, "w");
    char nome[100];
    int opcao,idade;
    float altura;

    if (file) {
        do {    //do while pra digitar varias pessoas e n só uma 
            printf("digite nome, idade, altura\n");
            scanf("%s %d %f",nome,&idade,&altura); //le dados
            fprintf(file,"%s %d %.2f\n",nome,idade,altura);  //escreve informações no arquivo||
            printf("digite 1 pra ler outra pessoa\n");
            scanf("%d",&opcao);
             
        }while (opcao == 1);
        
        fclose(file);

    } else {

        printf("\nERRO ao abrir arquivo!\n");
    }
}



void ler(char f[]) {

    FILE *file = fopen(f, "r");
    char nome[100];
    int idade;
    float altura;

    if (file) {
        printf("\tDados lidos do arquivo:\n");
        while (fscanf(file,"%s %d %f", nome, &idade, &altura) != -1) //-1 é quando da erro, n tem mais oq ser lido
            printf("nome: %s\n idade: %d\n altura: %.2f\n",nome,idade, altura);
        fclose(file);
    }
    else
        printf("\nERRO ao abrir arquivo!\n");
}


int main() {
    char nome[100] = {"conto.txt"};

    escrever(nome);
    ler(nome);

    return 0;
}