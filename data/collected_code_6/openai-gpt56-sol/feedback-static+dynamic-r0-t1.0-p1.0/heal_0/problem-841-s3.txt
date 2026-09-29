#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t merge_and_count(int *array, int *temp, size_t left,
                                size_t middle, size_t right)
{
    size_t i = left;
    size_t j = middle;
    size_t k = left;
    uint64_t inversions = 0;

    while (i < middle && j < right) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
            inversions += (uint64_t)(middle - i);
        }
    }

    while (i < middle) {
        temp[k++] = array[i++];
    }

    while (j < right) {
        temp[k++] = array[j++];
    }

    for (i = left; i < right; ++i) {
        array[i] = temp[i];
    }

    return inversions;
}

static uint64_t sort_and_count(int *array, int *temp, size_t left, size_t right)
{
    if (right - left < 2) {
        return 0;
    }

    size_t middle = left + (right - left) / 2;
    uint64_t inversions = sort_and_count(array, temp, left, middle);

    inversions += sort_and_count(array, temp, middle, right);
    inversions += merge_and_count(array, temp, left, middle, right);

    return inversions;
}

static int count_inversions(int *array, size_t length, uint64_t *result)
{
    int *temp;

    if (result == NULL || (array == NULL && length != 0)) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*temp)) {
        return -1;
    }

    if (length < 2) {
        *result = 0;
        return 0;
    }

    temp = malloc(length * sizeof(*temp));
    if (temp == NULL) {
        return -1;
    }

    *result = sort_and_count(array, temp, 0, length);
    free(temp);

    return 0;
}

int main(void)
{
    size_t length;
    int *array = NULL;
    uint64_t inversions;

    if (scanf("%zu", &length) != 1) {
        fprintf(stderr, "Failed to read array length.\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Array is too large.\n");
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
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