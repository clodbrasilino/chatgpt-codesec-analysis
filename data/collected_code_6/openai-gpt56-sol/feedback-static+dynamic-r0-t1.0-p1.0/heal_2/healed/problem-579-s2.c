#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *values, size_t length, int target)
{
    for (size_t i = 0; i < length; ++i) {
        if (values[i] == target) {
            return true;
        }
    }

    return false;
}

static int *find_dissimilar(const int *first, size_t first_length,
                            const int *second, size_t second_length,
                            size_t *result_length)
{
    if (result_length == NULL) {
        return NULL;
    }

    *result_length = 0;

    if ((first == NULL && first_length > 0) ||
        (second == NULL && second_length > 0) ||
        first_length > SIZE_MAX - second_length) {
        return NULL;
    }

    size_t capacity = first_length + second_length;

    if (capacity == 0 || capacity > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *result = malloc(capacity * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < first_length; ++i) {
        if (!contains(second, second_length, first[i]) &&
            !contains(result, *result_length, first[i])) {
            result[(*result_length)++] = first[i];
        }
    }

    for (size_t i = 0; i < second_length; ++i) {
        if (!contains(first, first_length, second[i]) &&
            !contains(result, *result_length, second[i])) {
            result[(*result_length)++] = second[i];
        }
    }

    if (*result_length == 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4, 5};
    const int second[] = {4, 5, 6, 7, 8};
    const size_t first_length = sizeof first / sizeof first[0];
    const size_t second_length = sizeof second / sizeof second[0];
    size_t result_length = 0;

    int *result = find_dissimilar(first, first_length,
                                  second, second_length,
                                  &result_length);

    if (result == NULL && result_length == 0) {
        bool has_dissimilar = false;

        for (size_t i = 0; i < first_length && !has_dissimilar; ++i) {
            has_dissimilar = !contains(second, second_length, first[i]);
        }

        for (size_t i = 0; i < second_length && !has_dissimilar; ++i) {
            has_dissimilar = !contains(first, first_length, second[i]);
        }

        if (has_dissimilar) {
            fputs("Unable to find dissimilar elements.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    putchar('[');

    for (size_t i = 0; i < result_length; ++i) {
        if (i > 0) {
            fputs(", ", stdout);
        }

        printf("%d", result[i]);
    }

    puts("]");
    free(result);

    return EXIT_SUCCESS;
}