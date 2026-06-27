int gbv_copia(const Library *lib, const char *docname, const char *origfile, const char *newfile) {

    int i;
    long offset, size, faltando, para_ler;
    char buffer[BUFFER_SIZE];
    SuperBlock sb;
    Document doc;

    if (!lib || lib->count == 0)
        return 1;

    for (i = 0; i < lib->count; i++) {

        if (strcmp(lib->docs[i].name, docname) == 0) {

            offset = lib->docs[i].offset;
            size = lib->docs[i].size;

            FILE *orig = fopen(origfile, "rb");
            if (!orig)
                return 1;

            if (gbv_create(newfile) != 0) {
                fclose(orig);
                return 1;
            }

            FILE *novo = fopen(newfile, "rb+");
            if (!novo) {
                fclose(orig);
                return 1;
            }

            /* copia apenas os bytes do documento */
            fseek(orig, offset, SEEK_SET);
            fseek(novo, sizeof(SuperBlock), SEEK_SET);

            faltando = size;
            while (faltando > 0) {

                para_ler = (faltando > BUFFER_SIZE) ? BUFFER_SIZE : faltando;

                if (fread(buffer, 1, para_ler, orig) != para_ler) {
                    fclose(orig);
                    fclose(novo);
                    return 1;
                }

                if (fwrite(buffer, 1, para_ler, novo) != para_ler) {
                    fclose(orig);
                    fclose(novo);
                    return 1;
                }

                faltando -= para_ler;
            }

            /* cria o único documento da nova biblioteca */
            strcpy(doc.name, lib->docs[i].name);
            doc.size = lib->docs[i].size;
            doc.date = lib->docs[i].date;
            doc.offset = sizeof(SuperBlock);

            /* atualiza superbloco */
            sb.num_docs = 1;
            sb.offset_dir = sizeof(SuperBlock) + doc.size;

            /* escreve diretório */
            fseek(novo, sb.offset_dir, SEEK_SET);
            if (fwrite(&doc, sizeof(Document), 1, novo) != 1) {
                fclose(orig);
                fclose(novo);
                return 1;
            }

            /* reescreve superbloco */
            fseek(novo, 0, SEEK_SET);
            if (fwrite(&sb, sizeof(SuperBlock), 1, novo) != 1) {
                fclose(orig);
                fclose(novo);
                return 1;
            }

            fclose(orig);
            fclose(novo);
            return 0;
        }
    }

    return 1;