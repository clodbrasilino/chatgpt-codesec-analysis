#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int count_unequal_pairs(int *array, size_t length, uint64_t *result)
{
    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    if (length > 1U) {
        qsort(array, length, sizeof(*array), compare_ints);
    }

    uint64_t equal_pairs = 0U;

    for (size_t i = 0U; i < length;) {
        size_t j = i + 1U;

        while (j < length && array[j] == array[i]) {
            ++j;
        }

        const uint64_t frequency = (uint64_t)(j - i);
        equal_pairs += frequency * (frequency - 1U) / 2U;
        i = j;
    }

    const uint64_t count = (uint64_t)length;
    *result = count * (count - 1U) / 2U - equal_pairs;

    return 0;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if ((uintmax_t)length > UINT64_MAX ||
        (uintmax_t)length > (uintmax_t)(SIZE_MAX / sizeof(int))) {
        return EXIT_FAILURE;
    }

    const uint64_t count = (uint64_t)length;

    if (count > 0U && count - 1U > UINT64_MAX / count) {
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length > 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    uint64_t unequal_pairs = 0U;

    if (count_unequal_pairs(array, length, &unequal_pairs) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", unequal_pairs) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}