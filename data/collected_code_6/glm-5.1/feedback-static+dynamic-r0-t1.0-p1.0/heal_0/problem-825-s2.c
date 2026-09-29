#include <stdio.h>
#include <stdlib.h>

int *access_elements(const int *list, size_t list_size, const size_t *indices, size_t indices_size, size_t *out_size) {
    if (list == NULL || indices == NULL || out_size == NULL) {
        return NULL;
    }

    if (indices_size == 0 || list_size == 0) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < indices_size; i++) {
        if (indices[i] >= list_size) {
            *out_size = 0;
            return NULL;
        }
    }

    int *result = malloc(indices_size * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < indices_size; i++) {
        result[i] = list[indices[i]];
    }

    *out_size = indices_size;
    return result;
}

int main(void) {
    int list[] = {10, 20, 30, 40, 50};
    size_t list_size = sizeof(list) / sizeof(list[0]);

    size_t indices[] = {0, 2, 4};
    size_t indices_size = sizeof(indices) / sizeof(indices[0]);

    size_t out_size;
    int *elements = access_elements(list, list_size, indices, indices_size, &out_size);

    if (elements != NULL) {
        for (size_t i = 0; i < out_size; i++) {
            printf("%d\n", elements[i]);
        }
        free(elements);
    }

    return 0;
}