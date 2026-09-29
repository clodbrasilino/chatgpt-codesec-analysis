#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

static int compare_ints(const void *a, const void *b)
{
    const int left = *(const int *)a;
    const int right = *(const int *)b;

    return (left > right) - (left < right);
}

static int find_smallest_missing(const int array[], size_t length, int *result)
{
    int *copy;
    int missing = 0;
    size_t i;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    if (length == 0U) {
        *result = 0;
        return 0;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0U; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    for (i = 0U; i < length; ++i) {
        if (copy[i] < missing) {
            continue;
        }

        if (copy[i] == missing) {
            if (missing == INT32_MAX) {
                free(copy);
                return -1;
            }
            ++missing;
        } else {
            break;
        }
    }

    free(copy);
    *result = missing;
    return 0;
}

int main(void)
{
    const int array[] = {0, 1, 2, 4, 6, 3, 7, 8};
    const size_t length = sizeof(array) / sizeof(array[0]);
    int missing;

    if (find_smallest_missing(array, length, &missing) != 0) {
        fputs("Unable to find the smallest missing number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", missing);
    return EXIT_SUCCESS;
}