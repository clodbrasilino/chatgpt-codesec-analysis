#include <stdio.h>
#include <stdlib.h>

static int find_last_removed_position(const int *original, size_t original_size,
                                      const int *remaining, size_t remaining_size,
                                      size_t *position)
{
    size_t i = 0;
    size_t j = 0;
    int found = 0;

    if (original == NULL || remaining == NULL || position == NULL ||
        remaining_size > original_size) {
        return -1;
    }

    while (i < original_size) {
        if (j < remaining_size && original[i] == remaining[j]) {
            ++j;
        } else {
            *position = i;
            found = 1;
        }
        ++i;
    }

    if (j != remaining_size || !found) {
        return -1;
    }

    return 0;
}

int main(void)
{
    size_t original_size;
    size_t remaining_size;
    size_t position;
    int *original = NULL;
    int *remaining = NULL;

    if (scanf("%zu", &original_size) != 1 || original_size == 0 ||
        original_size > SIZE_MAX / sizeof(*original)) {
        return EXIT_FAILURE;
    }

    original = malloc(original_size * sizeof(*original));
    if (original == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < original_size; ++i) {
        if (scanf("%d", &original[i]) != 1) {
            free(original);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu", &remaining_size) != 1 ||
        remaining_size >= original_size ||
        remaining_size > SIZE_MAX / sizeof(*remaining)) {
        free(original);
        return EXIT_FAILURE;
    }

    if (remaining_size > 0) {
        remaining = malloc(remaining_size * sizeof(*remaining));
        if (remaining == NULL) {
            free(original);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < remaining_size; ++i) {
            if (scanf("%d", &remaining[i]) != 1) {
                free(remaining);
                free(original);
                return EXIT_FAILURE;
            }
        }
    } else {
        remaining = original;
    }

    if (find_last_removed_position(original, original_size, remaining,
                                   remaining_size, &position) != 0) {
        if (remaining_size > 0) {
            free(remaining);
        }
        free(original);
        return EXIT_FAILURE;
    }

    printf("%zu\n", position);

    if (remaining_size > 0) {
        free(remaining);
    }
    free(original);

    return EXIT_SUCCESS;
}