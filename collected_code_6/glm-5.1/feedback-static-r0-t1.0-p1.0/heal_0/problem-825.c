#include <stdio.h>
#include <stdlib.h>

int *get_elements(const int *list, size_t list_size, const size_t *indices, size_t index_count) {
    if (list == NULL || indices == NULL) {
        return NULL;
    }

    int *result = malloc(index_count * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < index_count; i++) {
        if (indices[i] >= list_size) {
            free(result);
            return NULL;
        }
        result[i] = list[indices[i]];
    }

    return result;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50};
    size_t indices[] = {0, 2, 4};
    size_t list_size = sizeof(list) / sizeof(list[0]);
    size_t index_count = sizeof(indices) / sizeof(indices[0]);

    int *extracted = get_elements(list, list_size, indices, index_count);
    if (extracted == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < index_count; i++) {
        printf("%d\n", extracted[i]);
    }

    free(extracted);
    extracted = NULL;

    return EXIT_SUCCESS;
}