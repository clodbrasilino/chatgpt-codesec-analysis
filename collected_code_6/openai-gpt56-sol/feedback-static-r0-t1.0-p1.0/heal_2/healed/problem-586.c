#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    int *temporary;
    size_t temporary_bytes;

    if (array == NULL || length == 0 || split > length) {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return -1;
    }

    split %= length;
    if (split == 0) {
        return 0;
    }

    temporary_bytes = split * sizeof(*array);
    temporary = malloc(temporary_bytes);
    if (temporary == NULL) {
        return -1;
    }

    for (size_t i = 0; i < split; ++i) {
        temporary[i] = array[i];
    }

    for (size_t i = split; i < length; ++i) {
        array[i - split] = array[i];
    }

    for (size_t i = 0; i < split; ++i) {
        array[length - split + i] = temporary[i];
    }

    free(temporary);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, 4, 5, 6};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const size_t split = 2;

    if (rotate_left(array, length, split) != 0) {
        fputs("Failed to rotate the array.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (printf("%d%s", array[i], i + 1 < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}