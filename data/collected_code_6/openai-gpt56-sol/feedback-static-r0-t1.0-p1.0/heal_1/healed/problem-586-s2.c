#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    int *temporary;
    size_t right_length;
    size_t allocation_size;

    if (array == NULL || length == 0 || split > length) {
        return -1;
    }

    if (split == 0 || split == length) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return -1;
    }

    allocation_size = length * sizeof(*array);
    right_length = length - split;

    temporary = malloc(allocation_size);
    if (temporary == NULL) {
        return -1;
    }

    for (size_t i = 0; i < right_length; ++i) {
        temporary[i] = array[split + i];
    }

    for (size_t i = 0; i < split; ++i) {
        temporary[right_length + i] = array[i];
    }

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
        if (printf("%d%s", array[i], i + 1 == length ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}