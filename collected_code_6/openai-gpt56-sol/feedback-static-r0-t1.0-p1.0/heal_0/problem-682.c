#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int multiply_lists(const int *first, const int *second, int *result, size_t length)
{
    if ((first == NULL || second == NULL || result == NULL) && length != 0U) {
        return EINVAL;
    }

    for (size_t i = 0U; i < length; ++i) {
        result[i] = first[i] * second[i];
    }

    return 0;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {6, 7, 8, 9, 10};
    const size_t length = sizeof(first) / sizeof(first[0]);
    int *result = calloc(length, sizeof(*result));

    if (result == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    int status = multiply_lists(first, second, result, length);

    if (status != 0) {
        fputs("List multiplication failed\n", stderr);
        free(result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%d%s", result[i], i + 1U == length ? "\n" : " ") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}