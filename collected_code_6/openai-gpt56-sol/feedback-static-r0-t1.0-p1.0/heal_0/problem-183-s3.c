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
    size_t left = 0;
    size_t right = 1;
    size_t count = 0;

    if (array == NULL || length < 2 || k < 0) {
        return 0;
    }

    qsort(array, length, sizeof(*array), compare_ints);

    if (k == 0) {
        while (left < length) {
            size_t next = left + 1;

            while (next < length && array[next] == array[left]) {
                ++next;
            }

            if (next - left >= 2) {
                ++count;
            }

            left = next;
        }

        return count;
    }

    while (left < length && right < length) {
        long long difference;

        if (left == right) {
            ++right;
            continue;
        }

        difference = (long long)array[right] - (long long)array[left];

        if (difference < k) {
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
    }

    return count;
}

int main(void)
{
    size_t length;
    long long k;
    int *array = NULL;
    size_t result;

    if (scanf("%zu %lld", &length, &k) != 2) {
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

    result = count_distinct_pairs(array, length, k);

    if (printf("%zu\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}