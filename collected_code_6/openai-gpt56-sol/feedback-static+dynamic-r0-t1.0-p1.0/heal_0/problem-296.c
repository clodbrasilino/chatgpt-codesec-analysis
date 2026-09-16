#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t merge_and_count(int *array, int *temporary,
                                size_t left, size_t middle, size_t right)
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

static uint64_t count_range(int *array, int *temporary,
                            size_t left, size_t right)
{
    if (right - left < 2U) {
        return 0;
    }

    const size_t middle = left + (right - left) / 2U;
    uint64_t inversions = count_range(array, temporary, left, middle);

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

    *result = 0;

    if (length < 2U) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*temporary)) {
        return -1;
    }

    temporary = malloc(length * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    *result = count_range(array, temporary, 0U, length);
    free(temporary);

    return 0;
}

int main(void)
{
    int array[] = {2, 4, 1, 3, 5};
    const size_t length = sizeof(array) / sizeof(array[0]);
    uint64_t inversions;

    if (count_inversions(array, length, &inversions) != 0) {
        fputs("Failed to count inversions.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Inversions: %" PRIu64 "\n", inversions);
    return EXIT_SUCCESS;
}