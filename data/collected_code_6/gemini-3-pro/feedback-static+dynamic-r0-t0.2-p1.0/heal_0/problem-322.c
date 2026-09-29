#include <stdio.h>
#include <stdlib.h>

void find_min_indices(const int *list, size_t size, size_t **indices, size_t *count) {
    if (list == NULL || size == 0 || indices == NULL || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        if (indices != NULL) {
            *indices = NULL;
        }
        return;
    }

    int min_val = list[0];
    size_t min_count = 1;

    for (size_t i = 1; i < size; ++i) {
        if (list[i] < min_val) {
            min_val = list[i];
            min_count = 1;
        } else if (list[i] == min_val) {
            min_count++;
        }
    }

    *indices = (size_t *)malloc(min_count * sizeof(size_t));
    if (*indices == NULL) {
        *count = 0;
        return;
    }

    size_t idx = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] == min_val) {
            (*indices)[idx++] = i;
        }
    }

    *count = min_count;
}

int main(void) {
    int list[] = {5, 3, 9, 3, 7, 3, 8};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t *indices = NULL;
    size_t count = 0;

    find_min_indices(list, size, &indices, &count);

    if (indices != NULL) {
        for (size_t i = 0; i < count; ++i) {
            printf("%zu ", indices[i]);
        }
        printf("\n");
        free(indices);
    }

    return 0;
}