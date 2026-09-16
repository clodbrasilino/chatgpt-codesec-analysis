#include <stdio.h>
#include <stdlib.h>

static size_t count_even_xor_pairs(const int *values, size_t count)
{
    size_t even_count = 0;
    size_t odd_count = 0;

    for (size_t i = 0; i < count; ++i) {
        if ((values[i] & 1) == 0) {
            ++even_count;
        } else {
            ++odd_count;
        }
    }

    return (even_count * (even_count - 1) / 2) +
           (odd_count * (odd_count - 1) / 2);
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = NULL;

    if (count > 0) {
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

    printf("%zu\n", count_even_xor_pairs(values, count));
    free(values);

    return EXIT_SUCCESS;
}