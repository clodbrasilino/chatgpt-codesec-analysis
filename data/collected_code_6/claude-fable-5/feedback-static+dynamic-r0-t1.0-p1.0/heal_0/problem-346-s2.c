#include <stdio.h>
#include <stdlib.h>

unsigned long long entringer(int n, int k)
{
    unsigned long long **table;
    unsigned long long result;
    int i;
    int j;

    if (n < 0 || k < 0 || k > n) {
        return 0ULL;
    }

    if (n == 0 && k == 0) {
        return 1ULL;
    }

    table = malloc((size_t)(n + 1) * sizeof(*table));
    if (table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i <= n; i++) {
        table[i] = calloc((size_t)(n + 1), sizeof(**table));
        if (table[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(table[j]);
            }
            free(table);
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    table[0][0] = 1ULL;

    for (i = 1; i <= n; i++) {
        table[i][0] = 0ULL;
        for (j = 1; j <= i; j++) {
            table[i][j] = table[i][j - 1] + table[i - 1][i - j];
        }
    }

    result = table[n][k];

    for (i = 0; i <= n; i++) {
        free(table[i]);
    }
    free(table);

    return result;
}

int main(void)
{
    int n;
    int k;

    n = 4;
    k = 2;

    printf("Entringer number e(%d, %d) = %llu\n", n, k, entringer(n, k));

    n = 5;
    k = 3;

    printf("Entringer number e(%d, %d) = %llu\n", n, k, entringer(n, k));

    return EXIT_SUCCESS;
}