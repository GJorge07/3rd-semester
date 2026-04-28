#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "gbv.h"
#include "util.h"


int gbv_create(const char *filename) {

    FILE *file = fopen (filename,"wb");
    SuperBlock sb;
    
    if (file) {

        memset(&sb, 0, sizeof(SuperBlock));     /*inicializa com zeros*/
        sb.num_docs = 0;                        /*inicia com 0 docs*/
        sb.offset_dir = sizeof(SuperBlock);     /*define onde começa dir*/
        fwrite(&sb,sizeof(SuperBlock),1,file); /*escreve num de docs e offset do dir no arquivo*/
        fclose(file);
        return 0;

    }
    else 
        return 1;
    
}


int gbv_open(Library *lib, const char *filename) {

    FILE *file = fopen(filename,"rb");
    SuperBlock sb;

    if (!file)
        return 1;

    if (fread(&sb,sizeof(SuperBlock),1,file) != 1) {
        fclose(file);
        return 1;
    }

    lib->count = sb.num_docs;
    
    if (sb.num_docs > 0) {
        lib->docs = malloc(sb.num_docs * sizeof(Document));  

        if (!lib->docs)
            return 1;

        fseek(file, sb.offset_dir, SEEK_SET);
        if (fread(lib->docs,sizeof(Document),sb.num_docs,file) != sb.num_docs) { 
            fclose(file);
            return 1;
        }
    }
    else
        lib->docs = NULL;

    fclose(file);
    return 0;
}


int gbv_add(Library *lib, const char *archive, const char *docname) {

    int lidos,i;
    char buffer[BUFFER_SIZE];   /*espaço temporário pra copiar pedaços do arquivo*/
    long novo_offset;           /*guarda onde o novo arquivo será escrito dentro do .gbv*/

    FILE *file = fopen(docname,"rb");          /*abre o arquivo externo (o que queremos adicionar)*/
    FILE *filee = fopen(archive,"rb+");        /*abre gbv(arquivo) onde iremos escrever*/

    if (!file || ! filee)
        return 1;

    SuperBlock sb;
    Document doc;

    if(strcmp(archive,docname) == 0) 
        return 1;

    /*remove documento existente com mesmo nome*/
    for(i = 0; i < lib->count; i++) {
        
        if(strcmp(lib->docs[i].name,docname) == 0) {
            gbv_remove(lib, docname, archive);
            break;
        }
    }
    

    if(!fread(&sb,sizeof(SuperBlock),1,filee)) {   /*le superbloco do arquivo*/
        fclose(file);
        fclose(filee);
        return 1;
    }

    novo_offset = sb.offset_dir;   /*novo_offset recebe o começo do dir*/
 
    doc.size = 0;
    fseek(filee,novo_offset,SEEK_SET);
    lidos = fread(buffer, 1, BUFFER_SIZE, file);

    while (lidos > 0) {       /*guarda quantos bytes foram lidos do arquivo externo*/

        fwrite(buffer,1,lidos,filee);
        doc.size = doc.size + lidos;
        lidos = fread(buffer, 1, BUFFER_SIZE, file);

    }

    /*cria o documento*/
    doc.offset = novo_offset;   
    doc.date = time(NULL);   
    strcpy(doc.name, docname);  

    /*coloca o documento na library*/
    Document *temp = realloc(lib->docs, (lib->count + 1) * sizeof(Document)); /*aumenta o espaço pra mais um doc*/

    if (!temp)
        return 1;

    lib->docs = temp; 
 
    lib->docs[lib->count] = doc;       /*coloca elemento novo no final*/
    lib->count++;


    
    sb.num_docs = lib->count;
    sb.offset_dir = novo_offset + doc.size;

    fseek(filee,sb.offset_dir,SEEK_SET);
    fwrite(lib->docs,sizeof(Document),lib->count,filee);

    fseek(filee, 0, SEEK_SET);
    fwrite(&sb,sizeof(SuperBlock),1,filee);

    fclose(file);
    fclose(filee);

    return 0;
}


int gbv_remove(Library *lib, const char *docname, const char *filename) {

    int i,j;

    if(!lib || lib->count == 0)
        return 1;

    for(i = 0; i < lib->count; i++) {     /*percorre os documentos*/

        if(strcmp(lib->docs[i].name,docname) == 0) {      /*se achar o documento, remove ele movendo todos pra esq*/
            
            for(j = i; j < lib->count - 1; j++) 
                lib->docs[j] = lib->docs[j+1];
            
            lib->count--;

            FILE *file = fopen(filename,"rb+");            /*abre arquivo pra ler e escrever sem apagar nada*/
            SuperBlock sb;
        
            if (!file)
                return 1;
        
            if(!fread(&sb,sizeof(SuperBlock),1,file)) {         /*le superbloco do arquivo, mostra oq tem la*/

                fclose(file);
                return 1;

            }
                
            sb.num_docs = lib->count;             /*atualiza num docs, vai pro começo e atualiza os ARQUIVOS*/
            fseek(file, 0, SEEK_SET);
            fwrite(&sb,sizeof(SuperBlock),1,file);
        
            fseek(file, sb.offset_dir, SEEK_SET);           /*vai pro começo do dir e atualiza o diretório*/
            fwrite(lib->docs, sizeof(Document),lib->count,file);
        
            fclose(file);
        
            return 0;
        }
    }
    return 1;
}

int gbv_list(const Library *lib) {

    int i;
    char data[100];

    if(!lib || lib->count == 0) {

        printf("Não há documentos na biblioteca");            /*se nao existe lib ou nao existe docs*/
        return 1;

    }

    for (i = 0; i < lib->count ; i++) {               /*laço q percorre o vetor e imprime as informações de todos*/

        format_date(lib->docs[i].date,data,100);    /*transforma a data pra forma humana de enxergar*/

        printf("NOME: %s |  TAMANHO: %ld | DATA: %s  | OFFSET:  %ld \n",
            lib->docs[i].name,
            lib->docs[i].size,
            data,
            lib->docs[i].offset);  
            
    }

    return 0;
}



int gbv_view(const Library *lib, const char *docname, const char *filename) {

    int i,pos = 0;
    long offset,size;
    long max_blocos;
    size_t remaining, to_read;  /*bytes que faltam ler*/
    char buffer[BUFFER_SIZE + 1],x;

    if(!lib || lib->count == 0)
        return 1;

    for(i = 0; i < lib->count; i++) {     /*percorre os documentos*/

        if(strcmp(lib->docs[i].name,docname) == 0) {

            offset = lib->docs[i].offset;
            size = lib->docs[i].size;

            FILE *file = fopen(filename,"rb");
            if (!file)
                return 1;

            max_blocos = (size + BUFFER_SIZE - 1) / BUFFER_SIZE;  

            printf("Digite N para ir para o próximo bloco, P para ir ao bloco anterior ou Q para sair\n");
            x = 'N';  /*Começa com N pra imprimir o primeiro bloco*/
            while (x != 'Q') {

                if (x == 'N') {
                    if (pos >= max_blocos) {
                        printf("Fim do documento\n");
                        break;
                    }
                } else if (x == 'P') {
                    if (pos > 0) {
                        pos--;
                    } else {
                        printf("Você está no primeiro bloco\n");
                        scanf(" %c", &x);
                        continue;
                    }
                } else {
                    printf("Operação inválida\n");
                    scanf(" %c", &x);
                    continue;
                }

                memset(buffer, 0, BUFFER_SIZE + 1);   /*limpa o buffer*/                
                
                fseek(file, offset + (pos * BUFFER_SIZE), SEEK_SET);    

                remaining = size - (pos * BUFFER_SIZE);
                if (remaining <= 0) {
                    printf("Fim do documento\n");
                    break;
                }

                to_read = (remaining > BUFFER_SIZE) ? BUFFER_SIZE : remaining;
                size_t lidos = fread(buffer, 1, to_read, file);
                
                if(lidos > 0) {
                    fwrite(buffer, 1, lidos, stdout);
                    printf("\n");
                    
                    if (x == 'N') 
                        pos++;
                } else {
                    printf("Erro ao ler\n");
                    break;
                }

                scanf(" %c", &x);
            }
            
            fclose(file);
            return 0;
        }
    }
    return 1;
}

