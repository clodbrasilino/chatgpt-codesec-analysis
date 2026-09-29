#include <stdio.h>
#include <stdlib.h>

static int count_odd_xor_pairs(const int *values, size_t count, size_t *result)
{
    size_t even_count = 0;
    size_t odd_count = 0;

    if (result == NULL || (values == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if ((values[i] & 1) == 0) {
            ++even_count;
        } else {
            ++odd_count;
        }
    }

    if (odd_count != 0 && even_count > SIZE_MAX / odd_count) {
        return 0;
    }

    *result = even_count * odd_count;
    return 1;
}

int main(void)
{
    size_t count;
    size_t pair_count;
    int *values = NULL;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!count_odd_xor_pairs(values, count, &pair_count)) {
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", pair_count) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}