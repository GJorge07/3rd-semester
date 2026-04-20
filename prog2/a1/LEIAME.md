A1 - Prog 2 - 1/2026
Autor: Gabriel Dobrowolski Jorge
GRR: 20250938

Lista de arquivos: 

gbv.c -> Implementação das operações da biblioteca;
gbv.h -> Protótipo das estruturas da biblioteca;
util.c -> Implementação da função de transformação de data;
util.h -> Protótipo da função de transformação de data;
main.c -> Controle das opções da biblioteca;
makefile -> Compilação;
LEIAME


Dificuldades encontradas + bugs conhecidos:

    Logo no início do projeto da encontrei dificuldades por ser algo que não estou acostumado a fazer. A primeira dificuldade foi logo para implementar a struct SuperBlock, já que eu pensava que deveria utilizar de alguma outra estrutura já definida. Tardei um pouco a pegar o jeito e o ritmo do trabalho, a pensar "fora da caixa" para entender como funcionaria dentro de um computador o que eu estava aplicando. Após compreender melhor a lógica, os erros foram mais específicos:

    1-> Esqueci de fechar o arquivo (fclose) diversas vezes, o que fazia o programa falhar;
    2-> Tive dificuldade de entender o uso de ponteiro no fwrite, talvez por ter um pouco de dificuldade com o uso de ponteiros no geral;
    3-> Muitas vezes me confundia com o uso de memória, arquivo, library, documento... misturava eles, mexia no errado...
    4-> A função ADD foi bem complicada, demorei pra pegar a lógica principal ela de "sobrescrever" no diretório; nunca tinha usado realloc; deu seg fault algumas vezes;
    5-> View com certeza foi o que mais tive dificuldades, tava dando muitos erros pois eu tardei a pensar em todos os possíveis casos de erro, no limite dos blocos utilizando buffer, remaning, for read...


Alterações na estrutura do código: 

    *Criei a struct SuperBlock
    *Adicionei o parâmetro "filename" nas funções REMOVE e VIEW;
    *Adicionei a opção "-c" no main para criar arquivo;


