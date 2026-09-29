#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static size_t count_distinct_pairs(int *array, size_t length, long long k)
{
    size_t count = 0;
    size_t left = 0;
    size_t right = 0;

    if (array == NULL || length < 2 || k < 0) {
        return 0;
    }

    qsort(array, length, sizeof(*array), compare_ints);

    if (k == 0) {
        while (left < length) {
            right = left + 1;

            while (right < length && array[right] == array[left]) {
                ++right;
            }

            if (right - left >= 2) {
                ++count;
            }

            left = right;
        }

        return count;
    }

    right = 1;

    while (left < length && right < length) {
        const long long difference =
            (long long)array[right] - (long long)array[left];

        if (left == right || difference < k) {
            ++right;
        } else if (difference > k) {
            ++left;
        } else {
            const int left_value = array[left];
            const int right_value = array[right];

            ++count;

            while (left < length && array[left] == left_value) {
                ++left;
            }

            while (right < length && array[right] == right_value) {
                ++right;
            }
        }

        if (right <= left && left < length) {
            right = left + 1;
        }
    }

    return count;
}

int main(void)
{
    size_t length;
    long long k;
    int *array = NULL;

    if (scanf("%zu %lld", &length, &k) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));

        if (array == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_distinct_pairs(array, length, k));

    free(array);
    return EXIT_SUCCESS;
}