#include <stdio.h>
#include <stdlib.h>

static int find_last_removed_position(const int *original, size_t original_size,
                                      const int *remaining, size_t remaining_size,
                                      size_t *position)
{
    if (original == NULL || remaining == NULL || position == NULL ||
        original_size == 0 || remaining_size >= original_size) {
        return 0;
    }

    size_t original_index = 0;
    size_t remaining_index = 0;
    size_t last_removed = 0;
    int found = 0;

    while (original_index < original_size) {
        if (remaining_index < remaining_size &&
            original[original_index] == remaining[remaining_index]) {
            ++remaining_index;
        } else {
            last_removed = original_index;
            found = 1;
        }
        ++original_index;
    }

    if (!found || remaining_index != remaining_size) {
        return 0;
    }

    *position = last_removed;
    return 1;
}

int main(void)
{
    const int original[] = {10, 20, 30, 40, 50, 60};
    const int remaining[] = {10, 30, 50};
    const size_t original_size = sizeof(original) / sizeof(original[0]);
    const size_t remaining_size = sizeof(remaining) / sizeof(remaining[0]);
    size_t position = 0;

    if (!find_last_removed_position(original, original_size,
                                    remaining, remaining_size, &position)) {
        fputs("Unable to determine the last removed position.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", position) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}