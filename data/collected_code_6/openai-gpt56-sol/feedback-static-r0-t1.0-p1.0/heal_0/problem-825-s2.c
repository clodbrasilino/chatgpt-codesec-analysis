#include <stdio.h>
#include <stdlib.h>

static int get_elements_at_indices(const int *list,
                                   size_t list_length,
                                   const size_t *indices,
                                   size_t index_count,
                                   int *result)
{
    if ((list == NULL && list_length != 0) ||
        (indices == NULL && index_count != 0) ||
        (result == NULL && index_count != 0)) {
        return -1;
    }

    for (size_t i = 0; i < index_count; ++i) {
        if (indices[i] >= list_length) {
            return -1;
        }
    }

    for (size_t i = 0; i < index_count; ++i) {
        result[i] = list[indices[i]];
    }

    return 0;
}

int main(void)
{
    const int list[] = {10, 20, 30, 40, 50, 60};
    const size_t indices[] = {0, 2, 5};
    const size_t list_length = sizeof list / sizeof list[0];
    const size_t index_count = sizeof indices / sizeof indices[0];

    if (index_count > SIZE_MAX / sizeof(int)) {
        fputs("Allocation size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int *result = malloc(index_count * sizeof *result);
    if (result == NULL && index_count != 0) {
        fputs("Memory allocation failed.\n", stderr);
        return EXIT_FAILURE;
    }

    if (get_elements_at_indices(list, list_length, indices, index_count, result) != 0) {
        fputs("Invalid argument or index.\n", stderr);
        free(result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < index_count; ++i) {
        printf("%d%s", result[i], i + 1 == index_count ? "\n" : " ");
    }

    free(result);
    return EXIT_SUCCESS;
}