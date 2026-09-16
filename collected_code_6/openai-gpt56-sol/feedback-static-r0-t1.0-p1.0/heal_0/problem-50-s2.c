#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

static bool find_min_length_list(const size_t *lengths, size_t count,
                                 size_t *min_index, size_t *min_length)
{
    if (lengths == NULL || min_index == NULL || min_length == NULL || count == 0) {
        return false;
    }

    *min_index = 0;
    *min_length = lengths[0];

    for (size_t i = 1; i < count; ++i) {
        if (lengths[i] < *min_length) {
            *min_length = lengths[i];
            *min_index = i;
        }
    }

    return true;
}

int main(void)
{
    size_t list_count = 0;

    if (printf("Enter the number of lists: ") < 0 ||
        scanf("%zu", &list_count) != 1 ||
        list_count == 0 ||
        list_count > SIZE_MAX / sizeof(size_t)) {
        fputs("Invalid number of lists.\n", stderr);
        return EXIT_FAILURE;
    }

    size_t *lengths = malloc(list_count * sizeof(*lengths));
    if (lengths == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list_count; ++i) {
        if (printf("Enter length of list %zu: ", i + 1) < 0 ||
            scanf("%zu", &lengths[i]) != 1) {
            fputs("Invalid list length.\n", stderr);
            free(lengths);
            return EXIT_FAILURE;
        }
    }

    size_t min_index = 0;
    size_t min_length = 0;

    if (!find_min_length_list(lengths, list_count, &min_index, &min_length)) {
        fputs("Unable to find the minimum-length list.\n", stderr);
        free(lengths);
        return EXIT_FAILURE;
    }

    if (printf("List %zu has the minimum length: %zu\n",
               min_index + 1, min_length) < 0) {
        free(lengths);
        return EXIT_FAILURE;
    }

    free(lengths);
    return EXIT_SUCCESS;
}