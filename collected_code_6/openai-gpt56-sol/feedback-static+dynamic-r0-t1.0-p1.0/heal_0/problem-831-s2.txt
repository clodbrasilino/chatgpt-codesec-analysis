#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int count_equal_pairs(int *array, size_t length, size_t *pair_count)
{
    size_t total = 0;
    size_t i = 0;

    if (array == NULL || pair_count == NULL) {
        return -1;
    }

    qsort(array, length, sizeof(*array), compare_ints);

    while (i < length) {
        size_t j = i + 1;
        size_t count;

        while (j < length && array[j] == array[i]) {
            ++j;
        }

        count = j - i;
        if (count > 1) {
            size_t contribution;

            if (count - 1 > SIZE_MAX / count) {
                return -1;
            }

            contribution = count * (count - 1) / 2;
            if (contribution > SIZE_MAX - total) {
                return -1;
            }

            total += contribution;
        }

        i = j;
    }

    *pair_count = total;
    return 0;
}

int main(void)
{
    int values[] = {1, 2, 3, 1, 2, 1};
    const size_t length = sizeof(values) / sizeof(values[0]);
    size_t pair_count = 0;

    if (count_equal_pairs(values, length, &pair_count) != 0) {
        fputs("Failed to count equal pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", pair_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}