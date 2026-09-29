#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    int *temporary = NULL;

    if (array == NULL || length == 0 || split > length) {
        return -1;
    }

    if (split == 0 || split == length) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return -1;
    }

    temporary = malloc(length * sizeof(*temporary));
    if (temporary == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temporary, array + split, (length - split) * sizeof(*temporary));
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temporary + (length - split), array, split * sizeof(*temporary));
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(array, temporary, length * sizeof(*array));

    free(temporary);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, 4, 5, 6};
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t split = 2;

    if (rotate_left(array, length, split) != 0) {
        fputs("Failed to rotate array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1 == length ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}