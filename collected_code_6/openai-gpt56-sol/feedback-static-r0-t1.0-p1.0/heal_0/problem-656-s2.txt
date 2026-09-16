#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int minimum_absolute_difference_sum(int64_t *a, int64_t *b,
                                           size_t length, uint64_t *result)
{
    uint64_t sum = 0;

    if (a == NULL || b == NULL || result == NULL) {
        return -1;
    }

    qsort(a, length, sizeof(*a), compare_int64);
    qsort(b, length, sizeof(*b), compare_int64);

    for (size_t i = 0; i < length; ++i) {
        uint64_t difference;

        if (a[i] >= b[i]) {
            difference = (uint64_t)a[i] - (uint64_t)b[i];
        } else {
            difference = (uint64_t)b[i] - (uint64_t)a[i];
        }

        if (UINT64_MAX - sum < difference) {
            return -1;
        }

        sum += difference;
    }

    *result = sum;
    return 0;
}

static int read_array(int64_t *array, size_t length)
{
    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    size_t length;
    int64_t *a = NULL;
    int64_t *b = NULL;
    uint64_t result;
    int status = EXIT_FAILURE;

    errno = 0;
    if (scanf("%zu", &length) != 1 || length == 0 ||
        length > SIZE_MAX / sizeof(*a)) {
        goto cleanup;
    }

    a = malloc(length * sizeof(*a));
    b = malloc(length * sizeof(*b));

    if (a == NULL || b == NULL) {
        goto cleanup;
    }

    if (read_array(a, length) != 0 || read_array(b, length) != 0) {
        goto cleanup;
    }

    if (minimum_absolute_difference_sum(a, b, length, &result) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(b);
    free(a);
    return status;
}