#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int subtract_tuples(const int *first, const int *second,
                           int *result, size_t length)
{
    size_t i;

    if (first == NULL || second == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        result[i] = first[i] - second[i];
    }

    return 0;
}

int main(void)
{
    const int first[] = {10, 20, 30, 40};
    const int second[] = {1, 2, 3, 4};
    const size_t length = sizeof(first) / sizeof(first[0]);
    int *result;
    size_t i;

    if (length != sizeof(second) / sizeof(second[0])) {
        return EXIT_FAILURE;
    }

    result = malloc(length * sizeof(*result));
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (subtract_tuples(first, second, result, length) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        if (printf("%d%s", result[i], i + 1 < length ? " " : "\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}