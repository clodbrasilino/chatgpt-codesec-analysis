#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    int *temporary;
    size_t first_part_size;

    if (array == NULL || length == 0U) {
        return -1;
    }

    split %= length;
    if (split == 0U) {
        return 0;
    }

    if (split > SIZE_MAX / sizeof(*temporary)) {
        return -1;
    }

    first_part_size = split * sizeof(*temporary);
    temporary = malloc(first_part_size);
    if (temporary == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temporary, array, first_part_size);
    memmove(array, array + split, (length - split) * sizeof(*array));
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
    size_t index;

    if (rotate_left(array, length, split) != 0) {
        return EXIT_FAILURE;
    }

    for (index = 0U; index < length; ++index) {
        if (printf("%d%s", array[index], index + 1U < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}