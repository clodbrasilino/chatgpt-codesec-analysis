#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    const int x = *(const int *)a;
    const int y = *(const int *)b;

    return (x > y) - (x < y);
}

static size_t count_distinct_pairs(const int *array, size_t length, long long k)
{
    size_t left = 0;
    size_t right = 1;
    size_t count = 0;

    if (array == NULL || length < 2 || k < 0) {
        return 0;
    }

    while (right < length) {
        const long long difference =
            (long long)array[right] - (long long)array[left];

        if (left == right || difference < k) {
            ++right;
        } else if (difference > k) {
            ++left;
        } else {
            ++count;

            const int left_value = array[left];
            const int right_value = array[right];

            while (left < length && array[left] == left_value) {
                ++left;
            }

            while (right < length && array[right] == right_value) {
                ++right;
            }
        }

        if (right <= left) {
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

    if (scanf("%zu %lld", &length, &k) != 2 || k < 0) {
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
            perror("malloc");
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

    if (length > 1) {
        qsort(array, length, sizeof(*array), compare_ints);
    }

    printf("%zu\n", count_distinct_pairs(array, length, k));

    free(array);
    return EXIT_SUCCESS;
}