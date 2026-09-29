#include <stdio.h>
#include <stdlib.h>

static int count_even_xor_pairs(const int *values, size_t count, size_t *result)
{
    size_t even_count = 0;
    size_t odd_count;

    if (result == NULL || (values == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if ((values[i] & 1) == 0) {
            ++even_count;
        }
    }

    odd_count = count - even_count;

    if (even_count > 1 && even_count > SIZE_MAX / (even_count - 1)) {
        return 0;
    }

    if (odd_count > 1 && odd_count > SIZE_MAX / (odd_count - 1)) {
        return 0;
    }

    size_t even_pairs = even_count * (even_count - 1) / 2;
    size_t odd_pairs = odd_count * (odd_count - 1) / 2;

    if (even_pairs > SIZE_MAX - odd_pairs) {
        return 0;
    }

    *result = even_pairs + odd_pairs;
    return 1;
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

    size_t pair_count;

    if (!count_even_xor_pairs(values, count, &pair_count)) {
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