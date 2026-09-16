#include <stdio.h>
#include <stdlib.h>

static int delannoy(int n, unsigned long long *result);

static int delannoy(int n, unsigned long long *result)
{
    unsigned long long **table;
    int i;
    int j;

    if (n < 0 || result == NULL) {
        return -1;
    }

    table = malloc((size_t)(n + 1) * sizeof(unsigned long long *));
    if (table == NULL) {
        return -1;
    }

    for (i = 0; i <= n; i++) {
        table[i] = malloc((size_t)(n + 1) * sizeof(unsigned long long));
        if (table[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(table[j]);
            }
            free(table);
            return -1;
        }
    }

    for (i = 0; i <= n; i++) {
        table[i][0] = 1ULL;
        table[0][i] = 1ULL;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            table[i][j] = table[i - 1][j] + table[i][j - 1] + table[i - 1][j - 1];
        }
    }

    *result = table[n][n];

    for (i = 0; i <= n; i++) {
        free(table[i]);
    }
    free(table);

    return 0;
}

int main(void)
{
    int n;
    unsigned long long result;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || n > 30) {
        fprintf(stderr, "n must be between 0 and 30\n");
        return EXIT_FAILURE;
    }

    if (delannoy(n, &result) != 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("Delannoy number D(%d, %d) = %llu\n", n, n, result);

    return EXIT_SUCCESS;
}