#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

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

static uint64_t sort_and_count(int *array, int *temporary,
                               size_t left, size_t right)
{
    if (right - left < 2U) {
        return 0;
    }

    size_t middle = left + (right - left) / 2U;
    uint64_t inversions = sort_and_count(array, temporary, left, middle);

    inversions += sort_and_count(array, temporary, middle, right);
    inversions += merge_and_count(array, temporary, left, middle, right);

    return inversions;
}

static int count_inversions(int *array, size_t length, uint64_t *result)
{
    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    *result = 0;

    if (length < 2U) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return -1;
    }

    int *temporary = malloc(length * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    *result = sort_and_count(array, temporary, 0, length);
    free(temporary);

    return 0;
}

int main(void)
{
    size_t length;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int)) {
        return EXIT_FAILURE;
    }

    int *array = NULL;

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    uint64_t inversions;

    if (count_inversions(array, length, &inversions) != 0) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", inversions) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}