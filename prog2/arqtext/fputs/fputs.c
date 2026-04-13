#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    FILE *file;   //FILE é o tipo da var e file é o nome dela
    char texto[500];
    int c;   //pra ler o texto, já que "texto" é um vetor

    
    file =fopen("conto.txt","w+");    //w+ -> leitura E ESCRITA
                                

    if (file) {

        printf("Digite uma frase(1 caracter pra finalizar)\n");
        fgets(texto, sizeof(texto), file);         //le uma linha do teclado e coloca na variavel texto, usado no lugar do scanf pq scanf ia dar loop infinito pq do "ENTER". QUANDO FOR LER STRING USA FGETS
        
        while (strlen(texto) > 2) {      //enquanto tam do texto > 1  || 2 ali pq tem o \n do fgets

            fputs(texto,file);   //igual ao fputc mas pra STRING  
            fgets(texto, sizeof(texto), file);    //sizeof(texto) nesse caso é 500, poderia colocar 500 ali
              
        }
    }
}