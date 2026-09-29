#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int count_odd_xor_pairs(const int *values, size_t count, uint64_t *result)
{
    uint64_t even_count = 0;
    uint64_t odd_count = 0;

    if (result == NULL || (values == NULL && count != 0)) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if ((values[i] & 1) == 0) {
            ++even_count;
        } else {
            ++odd_count;
        }
    }

    if (odd_count != 0 && even_count > UINT64_MAX / odd_count) {
        return -1;
    }

    *result = even_count * odd_count;
    return 0;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *values = NULL;

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

    uint64_t pair_count = 0;

    if (count_odd_xor_pairs(values, count, &pair_count) != 0) {
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", (unsigned long long)pair_count) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}