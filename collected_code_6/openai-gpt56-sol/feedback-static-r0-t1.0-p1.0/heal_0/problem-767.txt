#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int left = *(const int *)lhs;
    const int right = *(const int *)rhs;

    return (left > right) - (left < right);
}

static int count_pairs(const int *values, size_t length, int target, uint64_t *count)
{
    int *sorted;
    size_t left;
    size_t right;
    uint64_t total = 0;

    if (count == NULL || (values == NULL && length != 0)) {
        return -1;
    }

    *count = 0;

    if (length < 2) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        return -1;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        sorted[i] = values[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    left = 0;
    right = length - 1;

    while (left < right) {
        const int64_t current_sum = (int64_t)sorted[left] + (int64_t)sorted[right];

        if (current_sum < (int64_t)target) {
            ++left;
        } else if (current_sum > (int64_t)target) {
            --right;
        } else if (sorted[left] == sorted[right]) {
            const uint64_t occurrences = (uint64_t)(right - left + 1);
            total += occurrences * (occurrences - 1) / 2;
            break;
        } else {
            uint64_t left_count = 1;
            uint64_t right_count = 1;

            while (left + 1 < right && sorted[left + 1] == sorted[left]) {
                ++left_count;
                ++left;
            }

            while (right > left + 1 && sorted[right - 1] == sorted[right]) {
                ++right_count;
                --right;
            }

            total += left_count * right_count;
            ++left;
            --right;
        }
    }

    free(sorted);
    *count = total;
    return 0;
}

int main(void)
{
    int values[] = {1, 5, 7, -1, 5};
    const size_t length = sizeof(values) / sizeof(values[0]);
    const int target = 6;
    uint64_t count;

    if (count_pairs(values, length, target, &count) != 0) {
        fputs("Failed to count pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Number of pairs: %" PRIu64 "\n", count);
    return EXIT_SUCCESS;
}