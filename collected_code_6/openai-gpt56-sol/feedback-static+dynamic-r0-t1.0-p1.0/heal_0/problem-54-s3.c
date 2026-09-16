#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

static int counting_sort(int *array, size_t length)
{
    if (array == NULL && length != 0) {
        return -1;
    }

    if (length < 2) {
        return 0;
    }

    int minimum = array[0];
    int maximum = array[0];

    for (size_t i = 1; i < length; ++i) {
        if (array[i] < minimum) {
            minimum = array[i];
        }
        if (array[i] > maximum) {
            maximum = array[i];
        }
    }

    int64_t range_value = (int64_t)maximum - (int64_t)minimum + 1;
    if (range_value <= 0 || (uint64_t)range_value > SIZE_MAX / sizeof(size_t)) {
        return -1;
    }

    size_t range = (size_t)range_value;
    size_t *counts = calloc(range, sizeof(*counts));
    if (counts == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t index = (size_t)((int64_t)array[i] - (int64_t)minimum);
        if (counts[index] == SIZE_MAX) {
            free(counts);
            return -1;
        }
        ++counts[index];
    }

    size_t output_index = 0;
    for (size_t i = 0; i < range; ++i) {
        while (counts[i] > 0) {
            array[output_index++] = (int)((int64_t)minimum + (int64_t)i);
            --counts[i];
        }
    }

    free(counts);
    return 0;
}

int main(void)
{
    int array[] = {4, -2, 2, 8, 3, 3, 1, -2};
    size_t length = sizeof(array) / sizeof(array[0]);

    if (counting_sort(array, length) != 0) {
        fputs("Sorting failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1 == length ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}