/*Escreva uma função que receba um vetor de números reais e um
operador (no formato de ponteiro para função) e aplique o operador
para cada célula no vetor. Considere os operadores: sqrt, cbrt, ceil, floor.
Por exemplo, suponha que o vetor seja {1.1,2.3,3.6,4.8,5.9} e o operador seja
floor, então o vetor resultante será {1.0,2.0,3.0,4.0,5.0}.*/

#include <stdio.h>
#include <math.h>

void aplicar(double *v, int n, double (*operacao)(double)) {
    for (int i = 0; i < n; i++)
        v[i] = operacao(v[i]);
}

int main() {
    double v[5];
    int escolha;

    printf("Digite 5 números: ");
    scanf("%lf %lf %lf %lf %lf", &v[0], &v[1], &v[2], &v[3], &v[4]);

    printf("Escolha a operação (1-floor, 2-ceil, 3-sqrt, 4-cbrt): ");
    scanf("%d", &escolha);

    if (escolha == 1)
        aplicar(v, 5, floor);
    else if (escolha == 2)
        aplicar(v, 5, ceil);
    else if (escolha == 3)
        aplicar(v, 5, sqrt);
    else if (escolha == 4)
        aplicar(v, 5, cbrt);

    printf("Resultado: ");
    for (int i = 0; i < 5; i++)
        printf("%.1f ", v[i]);
    printf("\n");

    return 0;
}