else if (strcmp(opcao, "-x") == 0 && argc >= 5) {

        if (gbv_copia(&lib, argv[3], biblioteca, argv[4]) != 0)
            printf("Não foi possível fazer a cópia do documento %s.\n", argv[3]);
        else
            printf("Documento %s copiado com sucesso para %s.\n", argv[3], argv[4]);
    }