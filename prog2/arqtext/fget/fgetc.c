#include <stdio.h>
#include <stdlib.h>


int main () {

    FILE *file;   //FILE é o tipo da var e file é o nome dela
    char letra;

    
    file =fopen("conto.txt","w+");    //w+ -> leitura E ESCRITA
                                

    if (file) {

        printf("Digite um caractere e pressione enter");
        scanf("%c",&letra);

        while (letra != '\n') {  
            fputc(letra,file);   
            scanf("%c",&letra);
        }

        rewind(file);    //ponteiro volta pro inicio do arquivo, usa só se fzr algo no main

        printf("texto lido do arquivo:\n");

        while (!feof(file)) {    //le e imprime o caractere enquanto nao chega no fim do arquivo || f end of file 
            letra = fgetc(file);  //retorna caractere por caractere a partir do começo
            printf ("%c", letra);
        }

        fclose(file);            

    }
    else 
        printf("Erro ao manipular arquivo");

        return 0;

}
