#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FPRINTF  ESCREVE NO ARQUIVO DE TEXTO

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


int main() {
    char nome[100] = {"conto.txt"};

    escrever(nome);

    return 0;
}

