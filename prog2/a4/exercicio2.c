#include <stdio.h>

// você vai precisar criar 3 funções de filtro
// cada uma recebe um double e retorna int (1=passa, 0=não passa)
int eh_aprovado(double nota) { 

    if (nota >= 6) 
        return 1;
    else  
        return 0;

}
int eh_reprovado(double nota) {

    if (nota < 6 )
        return 1;
    else 
        return 0;

 }
int eh_recuperacao(double nota){

    if (nota >= 4 && nota < 6)
        return 1;
    else
        return 0;

 }

//função filtrar recebe o vetor e o ponteiro para função
void filtrar(double *v, int n, int (*criterio)(double)) { 

    for (int i = 0; i < n; i++) {

        if (criterio(v[i]))
            printf("%.1f\n",v[i]);

    }
    printf("\n");


 }

int main() {

    int filtro;
    double v[6];

    printf("Digite 6 notas:");
    scanf("%lf %lf %lf %lf %lf %lf", &v[0], &v[1], &v[2], &v[3], &v[4], &v[5]);

    printf("Escolha o filtro: 1-aprovado, 2-reprovado, 3-recuperacao");
    scanf("%d",&filtro);

    if (filtro == 1)
        filtrar(v, 6, eh_aprovado);
    else if (filtro == 2)
        filtrar(v, 6, eh_reprovado);
    else if (filtro == 3)
        filtrar(v, 6, eh_recuperacao);

 }