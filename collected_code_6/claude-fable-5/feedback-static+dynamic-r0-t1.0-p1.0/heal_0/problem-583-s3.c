#include <stdio.h>
#include <stdlib.h>

unsigned long long catalan(unsigned int n)
{
    unsigned long long *table;
    unsigned long long result;
    unsigned int i;
    unsigned int j;

    table = calloc((size_t)n + 1U, sizeof(unsigned long long));
    if (table == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    table[0] = 1ULL;
    for (i = 1U; i <= n; i++) {
        table[i] = 0ULL;
        for (j = 0U; j < i; j++) {
            table[i] += table[j] * table[i - 1U - j];
        }
    }

    result = table[n];
    free(table);
    return result;
}

int main(void)
{
    unsigned int n;
    int scanned;

    printf("Enter n (0-35): ");
    scanned = scanf("%u", &n);
    if (scanned != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 35U) {
        fprintf(stderr, "Input too large: result would overflow\n");
        return EXIT_FAILURE;
    }

    printf("Catalan(%u) = %llu\n", n, catalan(n));
    return EXIT_SUCCESS;
}