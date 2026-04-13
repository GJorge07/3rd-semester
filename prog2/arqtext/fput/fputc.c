#include <stdio.h>
#include <stdlib.h>


int main () {

    FILE *file;   //FILE é o tipo da var e file é o nome dela
    char letra;

    //"conto aqui poderia ser qlqr outro nome ou um caminho pra um diretório"
    file =fopen("conto.txt","w");//1 - nome do arquivo; 2 - w,r,a,w+,r+,a+(vide imagem)||se o arquivo n existe, é criado
                                

    if (file) {

        printf("Digite um texto e pressione enter");
        scanf("%c",&letra);

        while (letra != '\n') {  // \n = enter
            fputc(letra,file);   //escreve no arquivo até ENTER ser digitado
            scanf("%c",&letra);
        }

        fclose(file);            //Para de escrever

    }
    else 
        printf("Erro ao manipular arquivo");

}
