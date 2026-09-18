#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static long long count_sequences(int m, int n)
{
    long long **table;
    long long result;
    long long a;
    long long b;
    int i;
    int j;

    if (m < 0 || n < 0) {
        return -1LL;
    }

    if (n == 0) {
        return 1LL;
    }

    if (m == 0) {
        return 0LL;
    }

    table = malloc((size_t)(n + 1) * sizeof(long long *));
    if (table == NULL) {
        return -1LL;
    }

    for (i = 0; i <= n; i++) {
        table[i] = malloc((size_t)(m + 1) * sizeof(long long));
        if (table[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(table[j]);
            }
            free(table);
            return -1LL;
        }
    }

    for (j = 0; j <= m; j++) {
        table[0][j] = 1LL;
    }

    for (i = 1; i <= n; i++) {
        table[i][0] = 0LL;
    }

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            a = table[i][j - 1];
            b = table[i - 1][j / 2];
            if (a > LLONG_MAX - b) {
                for (i = 0; i <= n; i++) {
                    free(table[i]);
                }
                free(table);
                return -1LL;
            }
            table[i][j] = a + b;
        }
    }

    result = table[n][m];

    for (i = 0; i <= n; i++) {
        free(table[i]);
    }
    free(table);

    return result;
}

int main(void)
{
    int m;
    int n;
    long long answer;

    printf("Enter maximum value m: ");
    if (scanf("%d", &m) != 1) {
        fprintf(stderr, "Invalid input for m\n");
        return EXIT_FAILURE;
    }

    printf("Enter sequence length n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    if (m < 0 || n < 0) {
        fprintf(stderr, "Inputs must be non-negative\n");
        return EXIT_FAILURE;
    }

    answer = count_sequences(m, n);
    if (answer < 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("Number of possible sequences: %lld\n", answer);

    return EXIT_SUCCESS;
}