#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static void merge(int *array, int *buffer, size_t left, size_t middle, size_t right)
{
    size_t i = left;
    size_t j = middle;
    size_t k = left;

    while (i < middle && j < right) {
        if (array[i] <= array[j]) {
            buffer[k++] = array[i++];
        } else {
            buffer[k++] = array[j++];
        }
    }

    while (i < middle) {
        buffer[k++] = array[i++];
    }

    while (j < right) {
        buffer[k++] = array[j++];
    }

    for (i = left; i < right; ++i) {
        array[i] = buffer[i];
    }
}

static void merge_sort_range(int *array, int *buffer, size_t left, size_t right)
{
    size_t middle;

    if (right - left < 2U) {
        return;
    }

    middle = left + (right - left) / 2U;
    merge_sort_range(array, buffer, left, middle);
    merge_sort_range(array, buffer, middle, right);
    merge(array, buffer, left, middle, right);
}

static int merge_sort(int *array, size_t length)
{
    int *buffer;

    if (length < 2U) {
        return 0;
    }

    if (array == NULL || length > SIZE_MAX / sizeof(*buffer)) {
        return -1;
    }

    buffer = malloc(length * sizeof(*buffer));
    if (buffer == NULL) {
        return -1;
    }

    merge_sort_range(array, buffer, 0U, length);
    free(buffer);

    return 0;
}

int main(void)
{
    int array[] = {38, 27, 43, 3, 9, 82, 10};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t i;

    if (merge_sort(array, length) != 0) {
        fputs("Failed to sort the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1U == length ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}