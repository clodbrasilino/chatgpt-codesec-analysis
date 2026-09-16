#include <stdio.h>
#include <stdlib.h>

unsigned long long bell_number(int n)
{
    unsigned long long **triangle;
    unsigned long long result;
    int i;
    int j;

    if (n < 0) {
        return 0ULL;
    }

    triangle = malloc((size_t)(n + 1) * sizeof(*triangle));
    if (triangle == NULL) {
        return 0ULL;
    }

    for (i = 0; i <= n; i++) {
        triangle[i] = malloc((size_t)(i + 1) * sizeof(**triangle));
        if (triangle[i] == NULL) {
            for (j = 0; j < i; j++) {
                free(triangle[j]);
            }
            free(triangle);
            return 0ULL;
        }
    }

    triangle[0][0] = 1ULL;
    for (i = 1; i <= n; i++) {
        triangle[i][0] = triangle[i - 1][i - 1];
        for (j = 1; j <= i; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i][j - 1];
        }
    }

    result = triangle[n][0];

    for (i = 0; i <= n; i++) {
        free(triangle[i]);
    }
    free(triangle);

    return result;
}

int main(void)
{
    int n;
    unsigned long long bell;

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || n > 25) {
        fprintf(stderr, "n must be between 0 and 25\n");
        return EXIT_FAILURE;
    }

    bell = bell_number(n);
    printf("Bell number B(%d) = %llu\n", n, bell);

    return EXIT_SUCCESS;
}