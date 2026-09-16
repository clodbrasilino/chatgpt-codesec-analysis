#include <stdio.h>
#include <stdlib.h>

static int eulerian(unsigned int n, unsigned int m, unsigned long long *result)
{
    unsigned long long *prev;
    unsigned long long *curr;
    unsigned int i;
    unsigned int j;

    if (result == NULL) {
        return -1;
    }

    if (m > n) {
        *result = 0ULL;
        return 0;
    }

    prev = calloc((size_t)n + 1U, sizeof(unsigned long long));
    if (prev == NULL) {
        return -1;
    }

    curr = calloc((size_t)n + 1U, sizeof(unsigned long long));
    if (curr == NULL) {
        free(prev);
        return -1;
    }

    prev[0] = 1ULL;

    for (i = 1U; i <= n; i++) {
        curr[0] = 1ULL;
        for (j = 1U; j <= m && j <= i; j++) {
            curr[j] = (unsigned long long)(i - j) * prev[j - 1U]
                    + (unsigned long long)(j + 1U) * prev[j];
        }
        for (j = 0U; j <= m && j <= i; j++) {
            prev[j] = curr[j];
        }
    }

    *result = prev[m];

    free(prev);
    free(curr);
    return 0;
}

int main(void)
{
    unsigned int n;
    unsigned int m;
    unsigned long long value;

    for (n = 0U; n <= 8U; n++) {
        for (m = 0U; m <= n; m++) {
            if (eulerian(n, m, &value) != 0) {
                fprintf(stderr, "Computation failed for n=%u m=%u\n", n, m);
                return EXIT_FAILURE;
            }
            if (printf("A(%u, %u) = %llu\n", n, m, value) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}