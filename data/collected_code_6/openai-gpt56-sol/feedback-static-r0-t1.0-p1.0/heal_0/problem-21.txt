#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int find_multiples(int64_t n, size_t m, int64_t **multiples)
{
    if (multiples == NULL || n == 0 || m == 0 ||
        m > SIZE_MAX / sizeof(**multiples)) {
        return -1;
    }

    int64_t *result = malloc(m * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < m; ++i) {
        if (n > INT64_MAX / (int64_t)(i + 1) ||
            n < INT64_MIN / (int64_t)(i + 1)) {
            free(result);
            return -1;
        }

        result[i] = n * (int64_t)(i + 1);
    }

    *multiples = result;
    return 0;
}

int main(void)
{
    int64_t n;
    size_t m;
    int64_t *multiples = NULL;

    if (scanf("%" SCNd64 " %zu", &n, &m) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_multiples(n, m, &multiples) != 0) {
        fputs("Unable to generate multiples\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < m; ++i) {
        printf("%" PRId64 "%c", multiples[i], i + 1 == m ? '\n' : ' ');
    }

    free(multiples);
    return EXIT_SUCCESS;
}