#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gbv.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {

        printf("Uso: %s <opção> <biblioteca> [documentos...]\n", argv[0]);
        return 1;

    }

    const char *opcao = argv[1];
    const char *biblioteca = argv[2];

    Library lib;

    //criei essa parte
    if (strcmp(opcao, "-c") == 0) {

    if (gbv_create(biblioteca) != 0) {
        printf("Erro ao criar biblioteca %s\n", biblioteca);
        return 1;
    }

    printf("Biblioteca %s criada com sucesso.\n", biblioteca);
    return 0;
    }

    if (gbv_open(&lib, biblioteca) != 0) {

        printf("Erro ao abrir biblioteca %s\n", biblioteca);
        return 1;

    }

    if (strcmp(opcao, "-a") == 0) {

        for (int i = 3; i < argc; i++) {
            if (gbv_add(&lib, biblioteca, argv[i]) == 0)
                printf("Documento %s adicionado com sucesso.\n", argv[i]);
            else
                printf("Não foi possível adicionar o documento %s.\n", argv[i]);
        }
        
    }

    else if (strcmp(opcao, "-r") == 0) {
        
        for (int i = 3; i < argc; i++) {

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

