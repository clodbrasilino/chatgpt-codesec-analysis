#include <stdio.h>
#include <stdlib.h>

static int find_last_removed_position(const int original[],
                                      size_t original_size,
                                      const int remaining[],
                                      size_t remaining_size,
                                      size_t *position)
{
    size_t i = 0;
    size_t j = 0;
    size_t last = 0;
    int found = 0;

    if (original == NULL || remaining == NULL || position == NULL ||
        remaining_size > original_size) {
        return 0;
    }

    while (i < original_size) {
        if (j < remaining_size && original[i] == remaining[j]) {
            ++j;
        } else {
            last = i;
            found = 1;
        }
        ++i;
    }

    if (!found || j != remaining_size) {
        return 0;
    }

    *position = last;
    return 1;
}

int main(void)
{
    int original[] = {10, 20, 30, 40, 50};
    int remaining[] = {10, 30, 50};
    size_t position = 0;

    if (!find_last_removed_position(
            original,
            sizeof original / sizeof original[0],
            remaining,
            sizeof remaining / sizeof remaining[0],
            &position)) {
        fputs("Unable to determine the last removed position.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", position);
    return EXIT_SUCCESS;
}