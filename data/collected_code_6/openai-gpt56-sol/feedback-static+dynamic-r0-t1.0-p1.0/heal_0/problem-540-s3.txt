#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int frequency_difference(const int *array, size_t length, size_t *difference)
{
    int *copy;
    size_t current_frequency = 1U;
    size_t minimum_frequency;
    size_t maximum_frequency;

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

    minimum_frequency = length;
    maximum_frequency = 0U;

    for (size_t i = 1U; i <= length; ++i) {
        if (i < length && copy[i] == copy[i - 1U]) {
            ++current_frequency;
        } else {
            if (current_frequency < minimum_frequency) {
                minimum_frequency = current_frequency;
            }
            if (current_frequency > maximum_frequency) {
                maximum_frequency = current_frequency;
            }
            current_frequency = 1U;
        }
    }

    *difference = maximum_frequency - minimum_frequency;
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