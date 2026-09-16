#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t merge_and_count(int *array, int *temporary, size_t left,
                                size_t middle, size_t right)
{
    size_t i = left;
    size_t j = middle;
    size_t k = left;
    uint64_t inversions = 0;

    while (i < middle && j < right) {
        if (array[i] <= array[j]) {
            temporary[k++] = array[i++];
        } else {
            temporary[k++] = array[j++];
            inversions += (uint64_t)(middle - i);
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

    return inversions;
}

static uint64_t count_range(int *array, int *temporary, size_t left,
                            size_t right)
{
    size_t middle;
    uint64_t inversions;

    if (right - left < 2U) {
        return 0;
    }

    middle = left + (right - left) / 2U;
    inversions = count_range(array, temporary, left, middle);
    inversions += count_range(array, temporary, middle, right);
    inversions += merge_and_count(array, temporary, left, middle, right);

    return inversions;
}

static int count_inversions(int *array, size_t length, uint64_t *result)
{
    int *temporary;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*temporary)) {
        return -1;
    }

    if (length < 2U) {
        *result = 0;
        return 0;
    }

    temporary = malloc(length * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    *result = count_range(array, temporary, 0, length);
    free(temporary);

    return 0;
}

int main(void)
{
    size_t length;
    int *array = NULL;
    uint64_t inversions;
    size_t i;

    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Failed to read array length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Array length is too large.\n");
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            fprintf(stderr, "Failed to read array element.\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (count_inversions(array, length, &inversions) != 0) {
        fprintf(stderr, "Failed to count inversions.\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", inversions);
    free(array);

    return EXIT_SUCCESS;
}