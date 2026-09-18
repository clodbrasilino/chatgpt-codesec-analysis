#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int* find_multiples(int n, int m) {
    if (m <= 0 || (size_t)m > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int* multiples = (int*)malloc((size_t)m * sizeof(int));
    if (multiples == NULL) {
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1724130190 * 2 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:346,execs:198,op:havoc,rep:1)
         */
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