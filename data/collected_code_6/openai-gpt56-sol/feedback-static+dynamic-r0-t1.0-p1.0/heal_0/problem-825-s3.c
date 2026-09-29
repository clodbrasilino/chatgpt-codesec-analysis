#include <stdio.h>
#include <stdlib.h>

static int get_elements(const int *list, size_t list_size,
                        const size_t *indices, size_t index_count,
                        int *result)
{
    if ((list == NULL && list_size > 0U) ||
        (indices == NULL && index_count > 0U) ||
        (result == NULL && index_count > 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < index_count; ++i) {
        if (indices[i] >= list_size) {
            return -1;
        }
    }

    for (size_t i = 0U; i < index_count; ++i) {
        result[i] = list[indices[i]];
    }

    return 0;
}

int main(void)
{
    const int list[] = {10, 20, 30, 40, 50, 60};
    const size_t indices[] = {0U, 2U, 5U};
    const size_t list_size = sizeof list / sizeof list[0];
    const size_t index_count = sizeof indices / sizeof indices[0];
    int *result = NULL;

    if (index_count > SIZE_MAX / sizeof *result) {
        fputs("Allocation size overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (index_count > 0U) {
        result = malloc(index_count * sizeof *result);
        if (result == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (get_elements(list, list_size, indices, index_count, result) != 0) {
        fputs("Invalid input or index\n", stderr);
        free(result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < index_count; ++i) {
        if (printf("%d%s", result[i], i + 1U < index_count ? " " : "\n") < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}