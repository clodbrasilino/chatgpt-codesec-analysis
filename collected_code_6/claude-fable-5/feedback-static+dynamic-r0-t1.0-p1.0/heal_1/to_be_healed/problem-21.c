#include <stdio.h>
#include <stdlib.h>

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
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 614327182 * 4 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:4413,execs:717,op:havoc,rep:2)
         */
        result[i] = n * (i + 1);
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
        fprintf(stderr, "Memory allocation failed\n");
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