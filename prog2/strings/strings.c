#include <stdio.h>
#include <string.h>


int main() {
 char string[101], copia[101];

 printf("Digite uma string: " );
 scanf("%s", string);

//retorna quantidade de caracteres
 printf("A string digitada tem %d caracteres!" , strlen(string)); 

 //Recebe, em ordem, o ponteiro paraonde a string base deve ser copiada (um vetor de char comtamanho suficiente) e o ponteiro para a string base; retorna oponteiro para a string copiada.
 strcpy(copia, string);
 printf("A string digitada foi: %s",copia);

    //igual a anterior mas recebe quantos caracteres no maximo devem ser copiados
 strncpy(copia, string, 4);
 printf("A string digitada foi: %s",copia);



//Recebe um ponteiro para string eum caractere qualquer; retorna oponteiro para a primeira ocorrênciado caractere na string fornecida. Senão houver ocorrências, retorna NULL (0). O STRRCHR FAZ O MESMO MAS RETORNA O ÚLTIMO E NAO O PRIMEIRO
char string[101], *busca;

 printf("Digite uma string: " );
 scanf("%s", string);

 busca = strchr(string, 'a');

 if (busca != 0)

 printf("O primeiro 'a' encontrado esta no indice %d", busca-string);
 else

 printf("Nao existe a letra 'a' nastring!");

 //STRSTR, STRDUP, STRTOK faltaram


}


