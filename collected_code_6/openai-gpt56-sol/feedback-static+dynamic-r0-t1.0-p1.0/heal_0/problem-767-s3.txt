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

static int count_pairs(const int *array, size_t length, int target, uint64_t *count)
{
    int *copy = NULL;
    size_t left = 0;
    size_t right;
    uint64_t result = 0;

    if (count == NULL || (length > 0 && array == NULL)) {
        return -1;
    }

    *count = 0;

    if (length < 2) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);
    right = length - 1;

    while (left < right) {
        const int64_t current_sum = (int64_t)copy[left] + copy[right];

        if (current_sum < target) {
            ++left;
        } else if (current_sum > target) {
            --right;
        } else if (copy[left] == copy[right]) {
            const uint64_t elements = (uint64_t)(right - left + 1);

            if (elements > 1 && elements > UINT64_MAX / (elements - 1)) {
                free(copy);
                return -1;
            }

            result = elements * (elements - 1) / 2;
            break;
        } else {
            const int left_value = copy[left];
            const int right_value = copy[right];
            uint64_t left_count = 0;
            uint64_t right_count = 0;

            while (left <= right && copy[left] == left_value) {
                ++left_count;
                ++left;
            }

            while (right >= left && copy[right] == right_value) {
                ++right_count;
                --right;
            }

            if (left_count > UINT64_MAX / right_count) {
                free(copy);
                return -1;
            }

            const uint64_t pairs = left_count * right_count;

            if (result > UINT64_MAX - pairs) {
                free(copy);
                return -1;
            }

            result += pairs;
        }
    }

    free(copy);
    *count = result;
    return 0;
}

int main(void)
{
    size_t length;
    int target;
    int *array = NULL;
    uint64_t pair_count;

    if (scanf("%zu %d", &length, &target) != 2) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (count_pairs(array, length, target, &pair_count) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", pair_count) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}