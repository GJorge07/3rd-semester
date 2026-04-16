#include <stdio.h>
#include <stdlib.h>

#include "gbv.h"

//coloquei aq só pra ajudar a ver, TIRAR DEPOIS
#define MAX_NAME 256
#define BUFFER_SIZE 512   // tamanho fixo do buffer em bytes

// Estrutura de metadados de cada documento
typedef struct {

    char name[MAX_NAME];   // nome do documento
    long size;             // tamanho em bytes
    time_t date;           // data de inserção
    long offset;           // posição no container

} Document;

// Estrutura que representa a biblioteca (diretório em memória)
typedef struct {

    Document *docs;        // vetor dinâmico de documentos
    int count;             // número de documentos
    
} Library;


typedef struct {

    int num_docs;
    long offset_dir

}SuperBlock;

//pq usa &sb e nao só sb no fwrite (dificuldade 1)??
//qual a utilidade do superbloco(dificuldade 2)??
//tava fazendo sb.offset_dir receber NULL(dificuldade 3)
int gbv_create(const char *filename) {

    FILE *file = fopen (filename,"wb");
    SuperBlock sb;
    
    if (file) {

        sb.num_docs = 0;                   /*inicia com 0 docs*/
        sb.offset_dir = sizeof(SuperBlock); /*define onde começa dir*/
        fwrite(&sb,sizeof(SuperBlock),1,file); /*escreve num de docs e offset do dir no arquivo*/
        fclose(file);
        return 0;

    }
    else 

    return 1;
    
}

//Abre o arquivo .gbv, lê o índice (diretório), vai ate o dir e carrega todos os documentos pra memória (Library)
//depois dessa função, temos lib->count e lib>docs atualizados
//diferença de sb.num_docs pra count->library(dificuldade 4)?
int gbv_open(Library *lib, const char *filename) {

    FILE *file = fopen(filename,"rb");             /*le o arquivo*/

    SuperBlock sb;

    if (!file)
        return 1;

    if(!fread(&sb,sizeof(SuperBlock),1,file))         //le superbloco do arquivo
        return 1;

    lib->count = sb.num_docs;      /*atualiza num de docs da library*/
    if (sb.num_docs > 0) {

        lib->docs = malloc(sb.num_docs * sizeof(Document));    /*aloca espaço p todos os documentos*/

        if (!lib->docs)     /*se a alocação falhar*/
            return 1;

        fseek(file, sb.offset_dir, SEEK_SET);    /*vai pra onde começa o dir*/ 
        if(!fread(lib->docs,sizeof(Document),sb.num_docs,file))  {   /*preenche lib->docs*/
            free(lib->docs);
            return 1;
        }

        fclose(file);
    }
    else
        lib->docs = NULL;

    fclose(file);

    return 0;

}


//adiciona um novo arquivo gbv sobrescrevendo o diretório, dai empurrando tudo pra trás e trazendo o dir novamente, já que esta em memoria
//dificuldade em criar novo documento
int gbv_add(Library *lib, const char *archive, const char *docname) {

    int lidos,i;
    char buffer[BUFFER_SIZE];   /*espaço temporário pra copiar pedaços do arquivo*/
    long novo_offset;    /*guarda onde o novo arquivo será escrito dentro do .gbv*/
    char data[100];

    FILE *file = fopen(docname,"rb");          //abre o arquivo externo (o que você quer adicionar)
    FILE *filee = fopen(archive,"rb+");        //abre gbv(arquivo) onde iremos escrever

    if (!file || ! filee)
        return 1;

    SuperBlock sb;
    Document doc;

    if(!fread(&sb,sizeof(SuperBlock),1,filee))         //le superbloco do arquivo
        return 1;

    novo_offset = sb.offset_dir;   /*novo_offset recebe o começo do dir*/
 
    doc.size = 0;
    fseek(filee,novo_offset,SEEK_SET);
    lidos = fread(buffer, 1, BUFFER_SIZE, file);

    while (lidos > 0) {       /*guarda quantos bytes foram lidos do arquivo externo*/

        fwrite(buffer,1,lidos,filee);
        doc.size = doc.size + lidos;
        lidos = fread(buffer, 1, BUFFER_SIZE, file);

    }

    //cria o documento
    doc.offset = novo_offset;   //onde começou no .gbv
    doc.date = time(NULL);   //data atual
    strcpy(doc.name, docname);  //copia nome do arquivo

    //coloca o documento na library
    Document *temp = realloc(lib->docs, (lib->count + 1) * sizeof(Document)); // aumenta o espaço pra mais um doc

    if (!temp)
        return 1;

    lib->docs = temp; 
 
    lib->docs[lib->count] = doc;       //coloca elemento novo no final
    lib->count++;


    //
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

//precisei adicionar um novo parametro (filename) pra att o arquivo(dificuldade 6)
//pq faz fopen pra mexer em arquivo mas pra mexer em documento nao (dificuldade 7)
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
        
            if(!fread(&sb,sizeof(SuperBlock),1,file))         /*le superbloco do arquivo, mostra oq tem la*/
                return 1;
                
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


//dificuldade 5-> fomat_date
//lista todos os documentos e suas respectivas informações
//dificuldade 6 -> tava usando offset ao inves de count no laço (offset é d arquivo e count de array )
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

//usa document, superblock n, pq??
//falta mudar parametros no main e no .h
//tem q arrumar ainda
int gbv_view(const Library *lib, const char *docname, const char *filename) {

    int i,lidos,pos = 0;
    long offset,size;
    long max_blocos;
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

            max_blocos = (size + BUFFER_SIZE - 1) / BUFFER_SIZE;   //??

            printf("Digite N para ir para o próximo bloco, P para ir ao bloco anterior ou Q para sair");
            scanf(" %c",&x);
            while (x != 'Q') {

                fseek(file, offset + (pos * BUFFER_SIZE), SEEK_SET);    //??
                lidos = fread(buffer, 1, BUFFER_SIZE, file);
                if(lidos) {

                    buffer[lidos] = '\0';   //??
                    printf("%s", buffer);
                    scanf(" %c",&x);
                    if (x == 'N' && pos < max_blocos  -1 )
                        pos++;
                    else if (x == 'P' && pos > 0)
                        pos--;

                    }
                else {
                    printf ("Nao há arquivos");
                    return 0;
                }
                    
                }
            fclose(file);
            return 0;
        }
    }
    return 1;
}

