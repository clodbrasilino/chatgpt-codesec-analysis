#include <stdio.h>
#include <stdlib.h>

int access_elements(const int *list, size_t list_size,
                    const size_t *indices, size_t indices_count,
                    int *result)
{
    size_t i;

    if (list == NULL || indices == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < indices_count; i++) {
        if (indices[i] >= list_size) {
            return -1;
        }
        result[i] = list[indices[i]];
    }

    return 0;
}

int main(void)
{
    int list[] = {10, 20, 30, 40, 50, 60, 70};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t indices[] = {0, 2, 4, 6};
    size_t indices_count = sizeof(indices) / sizeof(indices[0]);
    int *result;
    size_t i;

    result = malloc(indices_count * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (access_elements(list, list_size, indices, indices_count, result) != 0) {
        fprintf(stderr, "Invalid input or index out of range\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < indices_count; i++) {
        printf("Element at index %zu: %d\n", indices[i], result[i]);
    }

    free(result);
    return EXIT_SUCCESS;
}