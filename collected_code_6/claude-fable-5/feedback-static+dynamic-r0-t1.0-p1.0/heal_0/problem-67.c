#include <stdio.h>
#include <stdlib.h>

#define MAX_N 25

static int bell_number(unsigned int n, unsigned long long *result)
{
    unsigned long long **triangle;
    unsigned int i;
    unsigned int j;

    if (result == NULL) {
        return -1;
    }

    if (n > MAX_N) {
        return -1;
    }

    if (n == 0U) {
        *result = 1ULL;
        return 0;
    }

    triangle = malloc((size_t)(n + 1U) * sizeof(*triangle));
    if (triangle == NULL) {
        return -1;
    }

    for (i = 0U; i <= n; i++) {
        triangle[i] = malloc((size_t)(i + 1U) * sizeof(**triangle));
        if (triangle[i] == NULL) {
            for (j = 0U; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return -1;
        }
    }

    triangle[0][0] = 1ULL;

    for (i = 1U; i <= n; i++) {
        triangle[i][0] = triangle[i - 1U][i - 1U];
        for (j = 1U; j <= i; j++) {
            triangle[i][j] = triangle[i - 1U][j - 1U] + triangle[i][j - 1U];
        }
    }

    *result = triangle[n][0];

    for (i = 0U; i <= n; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return 0;
}

int main(void)
{
    unsigned int n;
    unsigned long long result;
    int status;

    printf("Enter set size (0-%d): ", MAX_N);

    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    status = bell_number(n, &result);
    if (status != 0) {
        fprintf(stderr, "Computation failed: input out of range or memory error\n");
        return EXIT_FAILURE;
    }

    printf("Number of ways to partition a set of %u elements: %llu\n", n, result);

    return EXIT_SUCCESS;
}