#include <stdio.h>
#include <stdlib.h>

int find_multiples(int n, int m, long long **result)
{
    long long *arr;
    int i;

    if (result == NULL || m <= 0) {
        return -1;
    }

    arr = malloc((size_t)m * sizeof(long long));
    if (arr == NULL) {
        return -1;
    }

    for (i = 0; i < m; i++) {
        arr[i] = (long long)n * (i + 1);
    }

    *result = arr;
    return 0;
}

int main(void)
{
    int n;
    int m;
    int i;
    long long *multiples = NULL;

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
        fprintf(stderr, "Count m must be positive\n");
        return EXIT_FAILURE;
    }

    if (find_multiples(n, m, &multiples) != 0) {
        fprintf(stderr, "Failed to compute multiples\n");
        return EXIT_FAILURE;
    }

    printf("First %d multiples of %d:\n", m, n);
    for (i = 0; i < m; i++) {
        printf("%lld\n", multiples[i]);
    }

    free(multiples);
    multiples = NULL;

    return EXIT_SUCCESS;
}