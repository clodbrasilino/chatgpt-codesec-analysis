#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void merge(int array[], int temporary[], size_t left, size_t middle,
                  size_t right)
{
    size_t i = left;
    size_t j = middle;
    size_t k = left;

    while (i < middle && j < right) {
        if (array[i] <= array[j]) {
            temporary[k++] = array[i++];
        } else {
            temporary[k++] = array[j++];
        }
    }

    while (i < middle) {
        temporary[k++] = array[i++];
    }

    while (j < right) {
        temporary[k++] = array[j++];
    }

    for (i = left; i < right; ++i) {
        array[i] = temporary[i];
    }
}

static void merge_sort_range(int array[], int temporary[], size_t left,
                             size_t right)
{
    size_t middle;

    if (right - left < 2U) {
        return;
    }

    middle = left + (right - left) / 2U;
    merge_sort_range(array, temporary, left, middle);
    merge_sort_range(array, temporary, middle, right);
    merge(array, temporary, left, middle, right);
}

static int merge_sort(int array[], size_t length)
{
    int *temporary;

    if (length < 2U) {
        return 0;
    }

    if (array == NULL || length > SIZE_MAX / sizeof(*temporary)) {
        return -1;
    }

    temporary = malloc(length * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    merge_sort_range(array, temporary, 0U, length);
    free(temporary);

    return 0;
}

int main(void)
{
    int array[] = {38, 27, 43, 3, 9, 82, 10};
    const size_t length = sizeof(array) / sizeof(array[0]);
    size_t i;

    if (merge_sort(array, length) != 0) {
        fputs("Unable to sort the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1U == length ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}