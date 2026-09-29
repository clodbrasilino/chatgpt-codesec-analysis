#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

static int counting_sort(int *array, size_t length)
{
    int min_value;
    int max_value;
    uintmax_t range_value;
    size_t range;
    size_t *counts;
    size_t i;
    size_t output_index = 0;

    if (array == NULL && length != 0) {
        return -1;
    }

    if (length < 2) {
        return 0;
    }

    min_value = array[0];
    max_value = array[0];

    for (i = 1; i < length; ++i) {
        if (array[i] < min_value) {
            min_value = array[i];
        }
        if (array[i] > max_value) {
            max_value = array[i];
        }
    }

    range_value = (uintmax_t)((intmax_t)max_value - (intmax_t)min_value) + 1U;

    if (range_value > SIZE_MAX ||
        (size_t)range_value > SIZE_MAX / sizeof(*counts)) {
        return -1;
    }

    range = (size_t)range_value;
    counts = calloc(range, sizeof(*counts));
    if (counts == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        size_t index = (size_t)((intmax_t)array[i] - (intmax_t)min_value);

        if (counts[index] == SIZE_MAX) {
            free(counts);
            return -1;
        }
        ++counts[index];
    }

    for (i = 0; i < range; ++i) {
        while (counts[i] > 0) {
            array[output_index++] = (int)((intmax_t)min_value + (intmax_t)i);
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
    size_t i;

    if (counting_sort(array, length) != 0) {
        fputs("Counting sort failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1U == length ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}