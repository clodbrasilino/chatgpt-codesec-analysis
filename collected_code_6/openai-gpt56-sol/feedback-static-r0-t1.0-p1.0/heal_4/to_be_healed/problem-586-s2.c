#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    int *temporary;
    size_t element_size;
    size_t allocation_size;
    size_t left_size;
    size_t right_size;
    size_t right_length;

    if (array == NULL || length == 0 || split > length) {
        return -1;
    }

    if (split == 0 || split == length) {
        return 0;
    }

    element_size = sizeof(*array);

    if (length > SIZE_MAX / element_size) {
        return -1;
    }

    allocation_size = length * element_size;
    right_length = length - split;
    right_size = right_length * element_size;
    left_size = split * element_size;

    temporary = malloc(allocation_size);
    if (temporary == NULL) {
        return -1;
    }

    if (right_size > allocation_size ||
        left_size > allocation_size - right_size) {
        free(temporary);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temporary, array + split, right_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temporary + right_length, array, left_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(array, temporary, allocation_size);

    free(temporary);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, 4, 5, 6};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const size_t split = 2;

    if (rotate_left(array, length, split) != 0) {
        fputs("Failed to rotate array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        const char *separator = (i + 1 == length) ? "\n" : " ";

        if (printf("%d%s", array[i], separator) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}