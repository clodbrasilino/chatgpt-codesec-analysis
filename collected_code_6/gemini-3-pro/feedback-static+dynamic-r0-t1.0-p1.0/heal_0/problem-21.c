#include <stdio.h>
#include <stdlib.h>

int* find_multiples(int n, int m) {
    if (m <= 0) {
        return NULL;
    }

    int* multiples = (int*)malloc(m * sizeof(int));
    if (multiples == NULL) {
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        multiples[i] = n * (i + 1);
    }

    return multiples;
}

int main(void) {
    int n, m;

    if (scanf("%d %d", &n, &m) != 2) {
        return 1;
    }

    int* multiples = find_multiples(n, m);
    if (multiples == NULL) {
        return 1;
    }

    for (int i = 0; i < m; i++) {
        printf("%d ", multiples[i]);
    }
    printf("\n");

    free(multiples);

    return 0;
}