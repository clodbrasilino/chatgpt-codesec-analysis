#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    int *temporary;
    size_t first_part_size;
    size_t remaining_size;

    if (array == NULL || length == 0U) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return -1;
    }

    split %= length;
    if (split == 0U) {
        return 0;
    }

    first_part_size = split * sizeof(*array);
    remaining_size = (length - split) * sizeof(*array);

    temporary = malloc(first_part_size);
    if (temporary == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temporary, array, first_part_size);
    memmove(array, array + split, remaining_size);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(array + (length - split), temporary, first_part_size);

    free(temporary);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, 4, 5, 6};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const size_t split = 2U;

    if (rotate_left(array, length, split) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        const char *separator = index + 1U < length ? " " : "\n";

        if (printf("%d%s", array[index], separator) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}