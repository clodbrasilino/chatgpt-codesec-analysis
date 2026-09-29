#include <stdio.h>
#include <stdlib.h>

static int rearrange_alternating(int *array, size_t length)
{
    if (array == NULL && length != 0U) {
        return -1;
    }

    if (length < 2U) {
        return 0;
    }

    int *temporary = malloc(length * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    size_t positive = 0U;
    size_t negative = 0U;

    for (size_t i = 0U; i < length; ++i) {
        if (array[i] >= 0) {
            ++positive;
        } else {
            ++negative;
        }
    }

    size_t positive_index = 0U;
    size_t negative_index = positive;

    for (size_t i = 0U; i < length; ++i) {
        if (array[i] >= 0) {
            temporary[positive_index++] = array[i];
        } else {
            temporary[negative_index++] = array[i];
        }
    }

    positive_index = 0U;
    negative_index = positive;
    size_t output_index = 0U;
    int use_positive = positive >= negative;

    while (positive_index < positive && negative_index < length) {
        if (use_positive != 0) {
            array[output_index++] = temporary[positive_index++];
        } else {
            array[output_index++] = temporary[negative_index++];
        }
        use_positive = !use_positive;
    }

    while (positive_index < positive) {
        array[output_index++] = temporary[positive_index++];
    }

    while (negative_index < length) {
        array[output_index++] = temporary[negative_index++];
    }

    free(temporary);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, -4, -1, 4, -6, -8};
    const size_t length = sizeof(array) / sizeof(array[0]);

    if (rearrange_alternating(array, length) != 0) {
        fputs("Unable to rearrange the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < length; ++i) {
        if (printf("%s%d", i == 0U ? "" : " ", array[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}