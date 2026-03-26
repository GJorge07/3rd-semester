#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {

    int N;
    scanf("%d", &N);

    int m[1000];

    for(int i = 0; i < N; i++)
        scanf("%d", &m[i]);

    qsort(m, N, sizeof(int), cmp);

    int convidados = N / 2;

    int entrada_max = m[convidados - 1];
    int saida_min = m[convidados];

    int tempo = saida_min - entrada_max;

    printf("%d %d\n", convidados, tempo);

    return 0;
}