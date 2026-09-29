#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int rotate_left(int *array, size_t length, size_t split)
{
    if (array == NULL || length == 0U ||
        length > SIZE_MAX / sizeof(*array)) {
        return -1;
    }

    split %= length;
    if (split == 0U) {
        return 0;
    }

    const size_t first_count = split;
    const size_t remaining_count = length - split;
    const size_t first_size = first_count * sizeof(*array);
    const size_t remaining_size = remaining_count * sizeof(*array);

    int *temporary = malloc(first_size);
    if (temporary == NULL) {
        return -1;
    }

    memcpy(temporary, array, first_size);
    memmove(array, array + first_count, remaining_size);
    memcpy(array + remaining_count, temporary, first_size);

    free(temporary);
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 3, 4, 5, 6};
    const size_t length = sizeof(array) / sizeof(array[0]);

    if (rotate_left(array, length, 2U) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t index = 0U; index < length; ++index) {
        const char separator = index + 1U < length ? ' ' : '\n';

        if (printf("%d%c", array[index], separator) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}