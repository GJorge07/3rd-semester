#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "gbv.h"

int validar_chave(const char *filename, const char *key) {   /*função para validar a chave*/

    FILE *file = fopen(filename,"rb");
    char file_key[4];

    if (!file)
        return 1;

    if (fread(file_key, sizeof(char), 4, file) != 4) {
        fclose(file);
        return 1;
    }

    fclose(file);

    if (strncmp(file_key, key, 4) != 0) {
        printf("Acesso Negado\n");
        return 1;
    }   
    return 0;
}

int main(int argc, char *argv[]) {

    if (argc < 4) {

        printf("Uso: %s <chave> <opção> <biblioteca> [documentos...]\n", argv[0]);
        return 1;

    }
    const char *chave = argv[1];
    const char *opcao = argv[2];
    const char *biblioteca = argv[3];

    Library lib;

    //criei essa parte
    if (strcmp(opcao, "-c") == 0) {


    if (gbv_create(biblioteca, chave) != 0) {
        printf("Erro ao criar biblioteca %s\n", biblioteca);
        return 1;
    }

    printf("Biblioteca %s criada com sucesso.\n", biblioteca);
    return 0;
    }

    if (validar_chave(biblioteca, chave) != 0) {
        return 1;
    }

    if (gbv_open(&lib, biblioteca) != 0) {

        printf("Erro ao abrir biblioteca %s\n", biblioteca);
        return 1;

    }

    if (strcmp(opcao, "-a") == 0) {

        for (int i = 4; i < argc; i++) {
            if (gbv_add(&lib, biblioteca, argv[i]) == 0 )
                printf("Documento %s adicionado com sucesso.\n", argv[i]);
            else
                printf("Não foi possível adicionar o documento %s.\n", argv[i]);
        }
        
    }

    else if (strcmp(opcao, "-r") == 0) {
        
        for (int i = 4; i < argc; i++) {

            if (gbv_remove(&lib, argv[i], biblioteca) == 0)
                printf("Documento %s removido com sucesso.\n", argv[i]);
            else
                printf("Não foi possivel remover o documento %s.\n", argv[i]);

        }
        
    } else if (strcmp(opcao, "-l") == 0) {
        
        if (gbv_list(&lib) != 0)
            printf("Não foi possivel listar documentos.\n");

    } else if (strcmp(opcao, "-v") == 0 && argc >= 4) {

        if (gbv_view(&lib, argv[3], biblioteca) != 0)
            printf("Não foi possível visualizar os documentos. %s.\n", argv[3]);

    } 
     else {

        printf("Opção inválida.\n");

    }
    free(lib.docs);
    return 0;
}

