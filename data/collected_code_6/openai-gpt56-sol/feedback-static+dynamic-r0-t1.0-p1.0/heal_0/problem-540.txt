#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static int frequency_difference(const int *array, size_t length, size_t *difference)
{
    int *copy;
    size_t min_frequency;
    size_t max_frequency;
    size_t current_frequency;

    if (array == NULL || difference == NULL || length == 0U) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);

    min_frequency = length;
    max_frequency = 0U;
    current_frequency = 1U;

    for (size_t i = 1U; i < length; ++i) {
        if (copy[i] == copy[i - 1U]) {
            ++current_frequency;
        } else {
            if (current_frequency < min_frequency) {
                min_frequency = current_frequency;
            }
            if (current_frequency > max_frequency) {
                max_frequency = current_frequency;
            }
            current_frequency = 1U;
        }
    }

    if (current_frequency < min_frequency) {
        min_frequency = current_frequency;
    }
    if (current_frequency > max_frequency) {
        max_frequency = current_frequency;
    }

    *difference = max_frequency - min_frequency;
    free(copy);

    return 0;
}

int main(void)
{
    int array[] = {1, 2, 2, 3, 3, 3, 4, 4};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t difference;

    if (frequency_difference(array, length, &difference) != 0) {
        fputs("Unable to calculate the frequency difference.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", difference);
    return EXIT_SUCCESS;
}