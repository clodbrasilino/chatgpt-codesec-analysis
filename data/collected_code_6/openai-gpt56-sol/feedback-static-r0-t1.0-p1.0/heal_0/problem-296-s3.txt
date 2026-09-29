#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t merge_and_count(int *array, int *buffer, size_t left,
                                size_t middle, size_t right)
{
    size_t i = left;
    size_t j = middle;
    size_t k = left;
    uint64_t inversions = 0;

    while (i < middle && j < right) {
        if (array[i] <= array[j]) {
            buffer[k++] = array[i++];
        } else {
            buffer[k++] = array[j++];
            inversions += (uint64_t)(middle - i);
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

    return inversions;
}

static uint64_t count_range(int *array, int *buffer, size_t left, size_t right)
{
    uint64_t inversions;
    size_t middle;

    if (right - left < 2U) {
        return 0;
    }

    middle = left + (right - left) / 2U;
    inversions = count_range(array, buffer, left, middle);
    inversions += count_range(array, buffer, middle, right);
    inversions += merge_and_count(array, buffer, left, middle, right);

    return inversions;
}

static int count_inversions(int *array, size_t length, uint64_t *result)
{
    int *buffer;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    if (length < 2U) {
        *result = 0;
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*buffer)) {
        return -1;
    }

    buffer = malloc(length * sizeof(*buffer));
    if (buffer == NULL) {
        return -1;
    }

    *result = count_range(array, buffer, 0, length);
    free(buffer);

    return 0;
}

int main(void)
{
    int array[] = {8, 4, 2, 1};
    const size_t length = sizeof(array) / sizeof(array[0]);
    uint64_t inversions;

    if (count_inversions(array, length, &inversions) != 0) {
        fputs("Failed to count inversions.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", inversions) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}