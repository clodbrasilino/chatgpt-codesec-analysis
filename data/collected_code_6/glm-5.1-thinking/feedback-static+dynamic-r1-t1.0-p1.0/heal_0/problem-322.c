#include <stdio.h>
#include <stdlib.h>

size_t *find_min_indices(const int *arr, size_t size, size_t *out_count) {
    if (arr == NULL || size == 0 || out_count == NULL) {
        return NULL;
    }

    int min_val = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == min_val) {
            count++;
        }
    }

    size_t *indices = malloc(count * sizeof(size_t));
    if (indices == NULL) {
        return NULL;
    }

    size_t pos = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == min_val) {
            indices[pos++] = i;
        }
    }

    *out_count = count;
    return indices;
}

int main(void) {
    int arr[] = {4, 2, 5, 2, 8, 2, 1, 1, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t count = 0;

    size_t *indices = find_min_indices(arr, size, &count);

    if (indices != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%zu\n", indices[i]);
        }
        free(indices);
    }

    return 0;
}