#include <stdio.h>
#include <stdlib.h>

static int pairwise_add(const int *first, const int *second, int *result, size_t length)
{
    if (first == NULL || second == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        result[i] = first[i] + second[i];
    }

    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4};
    const int second[] = {5, 6, 7, 8};
    const size_t length = sizeof(first) / sizeof(first[0]);
    int *result = malloc(length * sizeof(*result));

    if (result == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (pairwise_add(first, second, result, length) != 0) {
        fputs("Pairwise addition failed.\n", stderr);
        free(result);
        return EXIT_FAILURE;
    }

    if (putchar('(') == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf(i + 1 < length ? "%d, " : "%d", result[i]) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    if (puts(")") == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}