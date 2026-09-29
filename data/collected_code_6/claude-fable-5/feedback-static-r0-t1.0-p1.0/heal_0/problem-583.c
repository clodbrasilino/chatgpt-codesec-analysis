#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int catalan(unsigned int n, unsigned long long *result)
{
    unsigned long long *table;
    unsigned int i;
    unsigned int j;

    if (result == NULL) {
        return -1;
    }

    table = calloc((size_t)n + 1U, sizeof(unsigned long long));
    if (table == NULL) {
        return -1;
    }

    table[0] = 1ULL;

    for (i = 1U; i <= n; i++) {
        table[i] = 0ULL;
        for (j = 0U; j < i; j++) {
            unsigned long long product;

            if (table[j] != 0ULL &&
                table[i - 1U - j] > ULLONG_MAX / table[j]) {
                free(table);
                return -2;
            }
            product = table[j] * table[i - 1U - j];

            if (table[i] > ULLONG_MAX - product) {
                free(table);
                return -2;
            }
            table[i] += product;
        }
    }

    *result = table[n];
    free(table);
    return 0;
}

int main(void)
{
    unsigned int n;
    unsigned long long value;
    int status;

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    status = catalan(n, &value);
    if (status == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    if (status == -2) {
        fprintf(stderr, "Overflow: result too large for n = %u\n", n);
        return EXIT_FAILURE;
    }

    printf("Catalan(%u) = %llu\n", n, value);
    return EXIT_SUCCESS;
}