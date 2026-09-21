#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    int *temporary;
    size_t split_bytes;
    size_t remaining_bytes;

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

    split_bytes = split * sizeof(*array);
    remaining_bytes = (length - split) * sizeof(*array);

    temporary = malloc(split_bytes);
    if (temporary == NULL) {
        return -1;
    }

    memmove(temporary, array, split_bytes);
    memmove(array, array + split, remaining_bytes);
    memmove(array + (length - split), temporary, split_bytes);

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
        if (printf("%d%s", array[index],
                   index + 1U < length ? " " : "\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}