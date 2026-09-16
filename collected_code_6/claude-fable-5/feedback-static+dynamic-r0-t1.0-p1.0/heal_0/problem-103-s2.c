#include <stdio.h>
#include <stdlib.h>

unsigned long long eulerian(int n, int m)
{
    unsigned long long *prev;
    unsigned long long *curr;
    unsigned long long result;
    int i;
    int j;

    if (n < 0 || m < 0 || m > n) {
        return 0ULL;
    }

    if (n == 0) {
        return (m == 0) ? 1ULL : 0ULL;
    }

    prev = calloc((size_t)(n + 1), sizeof(unsigned long long));
    if (prev == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    curr = calloc((size_t)(n + 1), sizeof(unsigned long long));
    if (curr == NULL) {
        free(prev);
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    prev[0] = 1ULL;

    for (i = 1; i <= n; i++) {
        for (j = 0; j <= i; j++) {
            unsigned long long left = (j > 0) ? prev[j - 1] : 0ULL;
            unsigned long long right = (j < i) ? prev[j] : 0ULL;
            curr[j] = (unsigned long long)(i - j) * left
                    + (unsigned long long)(j + 1) * right;
        }
        for (j = 0; j <= i; j++) {
            prev[j] = curr[j];
        }
    }

    result = prev[m];

    free(prev);
    free(curr);

    return result;
}

int main(void)
{
    int n;
    int m;

    n = 5;
    m = 2;
    printf("Eulerian(%d, %d) = %llu\n", n, m, eulerian(n, m));

    n = 7;
    m = 3;
    printf("Eulerian(%d, %d) = %llu\n", n, m, eulerian(n, m));

    n = 0;
    m = 0;
    printf("Eulerian(%d, %d) = %llu\n", n, m, eulerian(n, m));

    n = 4;
    m = 6;
    printf("Eulerian(%d, %d) = %llu\n", n, m, eulerian(n, m));

    return EXIT_SUCCESS;
}