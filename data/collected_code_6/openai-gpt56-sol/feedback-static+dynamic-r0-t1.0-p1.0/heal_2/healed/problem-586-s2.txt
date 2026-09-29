#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    int *temporary;
    size_t element_size = sizeof(*array);
    size_t total_bytes;
    size_t first_count;
    size_t first_bytes;
    size_t second_bytes;

    if (array == NULL || length == 0 || split > length) {
        return -1;
    }

    if (split == 0 || split == length) {
        return 0;
    }

    if (length > SIZE_MAX / element_size) {
        return -1;
    }

    total_bytes = length * element_size;
    first_count = length - split;
    first_bytes = first_count * element_size;
    second_bytes = split * element_size;

    temporary = malloc(total_bytes);
    if (temporary == NULL) {
        return -1;
    }

    memmove(temporary, array + split, first_bytes);
    memmove(temporary + first_count, array, second_bytes);
    memmove(array, temporary, total_bytes);

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