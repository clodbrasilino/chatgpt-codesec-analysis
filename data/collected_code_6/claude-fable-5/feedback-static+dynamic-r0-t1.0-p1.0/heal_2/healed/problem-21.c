#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *find_multiples(int n, int m)
{
    int *result;
    int i;

    if (m <= 0) {
        return NULL;
    }

    result = malloc((size_t)m * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < m; i++) {
        long long product = (long long)n * (long long)(i + 1);
        if (product > INT_MAX || product < INT_MIN) {
            free(result);
            return NULL;
        }
        result[i] = (int)product;
    }

    return result;
}

int main(void)
{
    int n;
    int m;
    int i;
    int *multiples;

    printf("Enter the number n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter the count m: ");
    if (scanf("%d", &m) != 1) {
        fprintf(stderr, "Invalid input for m\n");
        return EXIT_FAILURE;
    }

    if (m <= 0) {
        fprintf(stderr, "Count m must be a positive integer\n");
        return EXIT_FAILURE;
    }

    multiples = find_multiples(n, m);
    if (multiples == NULL) {
        fprintf(stderr, "Computation failed: allocation error or integer overflow\n");
        return EXIT_FAILURE;
    }

    printf("First %d multiples of %d:\n", m, n);
    for (i = 0; i < m; i++) {
        printf("%d\n", multiples[i]);
    }

    free(multiples);
    multiples = NULL;

    return EXIT_SUCCESS;
}