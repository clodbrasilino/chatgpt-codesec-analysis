#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    LIST_SUCCESS,
    LIST_INVALID_ARGUMENT,
    LIST_LENGTH_MISMATCH,
    LIST_ARITHMETIC_OVERFLOW,
    LIST_ALLOCATION_FAILURE
} ListStatus;

ListStatus subtract_lists(
    const int *first,
    size_t first_length,
    const int *second,
    size_t second_length,
    int **result,
    size_t *result_length
) {
    int *values;
    size_t i;

    if (result == NULL || result_length == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;
    *result_length = 0;

    if (first_length != second_length) {
        return LIST_LENGTH_MISMATCH;
    }

    if (first_length == 0) {
        return LIST_SUCCESS;
    }

    if (first == NULL || second == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    if (first_length > SIZE_MAX / sizeof(*values)) {
        return LIST_ALLOCATION_FAILURE;
    }

    values = malloc(first_length * sizeof(*values));
    if (values == NULL) {
        return LIST_ALLOCATION_FAILURE;
    }

    for (i = 0; i < first_length; ++i) {
        if ((second[i] > 0 && first[i] < INT_MIN + second[i]) ||
            (second[i] < 0 && first[i] > INT_MAX + second[i])) {
            free(values);
            return LIST_ARITHMETIC_OVERFLOW;
        }

        values[i] = first[i] - second[i];
    }

    *result = values;
    *result_length = first_length;
    return LIST_SUCCESS;
}

int print_list(const int *list, size_t length) {
    size_t i;

    if (length > 0 && list == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        if (i > 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (printf("%d", list[i]) < 0) {
            return -1;
        }
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

int main(void) {
    const int first[] = {10, 20, 30, 40, 50};
    const int second[] = {1, 2, 3, 4, 5};
    const size_t first_length = sizeof(first) / sizeof(first[0]);
    const size_t second_length = sizeof(second) / sizeof(second[0]);
    int *result = NULL;
    size_t result_length = 0;
    ListStatus status;

    status = subtract_lists(
        first,
        first_length,
        second,
        second_length,
        &result,
        &result_length
    );

    if (status != LIST_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (print_list(result, result_length) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}