#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int add_product(uint64_t *result, uint64_t first, uint64_t second)
{
    uint64_t product;

    if (first != 0 && second > UINT64_MAX / first) {
        return -1;
    }

    product = first * second;

    if (*result > UINT64_MAX - product) {
        return -1;
    }

    *result += product;
    return 0;
}

static int add_combinations(uint64_t *result, uint64_t elements)
{
    uint64_t first;
    uint64_t second;
    uint64_t pairs;

    if (elements < 2) {
        return 0;
    }

    if ((elements & UINT64_C(1)) == 0) {
        first = elements / 2;
        second = elements - 1;
    } else {
        first = elements;
        second = (elements - 1) / 2;
    }

    if (first != 0 && second > UINT64_MAX / first) {
        return -1;
    }

    pairs = first * second;

    if (*result > UINT64_MAX - pairs) {
        return -1;
    }

    *result += pairs;
    return 0;
}

static int count_pairs(const int *array, size_t length, int target,
                       uint64_t *count)
{
    int *copy;
    size_t left;
    size_t right;
    uint64_t result = 0;

    if (count == NULL || (length != 0 && array == NULL)) {
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

    left = 0;
    right = length - 1;

    while (left < right) {
        const int64_t sum = (int64_t)copy[left] + (int64_t)copy[right];

        if (sum < (int64_t)target) {
            ++left;
        } else if (sum > (int64_t)target) {
            --right;
        } else if (copy[left] == copy[right]) {
            const size_t range = right - left + 1;

            if (range > UINT64_MAX ||
                add_combinations(&result, (uint64_t)range) != 0) {
                free(copy);
                return -1;
            }

            break;
        } else {
            const int left_value = copy[left];
            const int right_value = copy[right];
            uint64_t left_count = 0;
            uint64_t right_count = 0;

            while (left <= right && copy[left] == left_value) {
                if (left_count == UINT64_MAX) {
                    free(copy);
                    return -1;
                }
                ++left_count;
                ++left;
            }

            while (right >= left && copy[right] == right_value) {
                if (right_count == UINT64_MAX) {
                    free(copy);
                    return -1;
                }
                ++right_count;
                --right;
            }

            if (add_product(&result, left_count, right_count) != 0) {
                free(copy);
                return -1;
            }
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

    if (length != 0) {
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