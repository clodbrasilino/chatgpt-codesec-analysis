#include <stdio.h>
#include <stdlib.h>

int* find_max_indices(const int* arr, size_t size, size_t* count) {
    if (arr == NULL || size == 0 || count == NULL) {
        *count = 0;
        return NULL;
    }

    int max_val = arr[0];
    for (size_t i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    *count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == max_val) {
            (*count)++;
        }
    }

    int* indices = (int*)malloc(*count * sizeof(int));
    if (indices == NULL) {
        *count = 0;
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == max_val) {
            indices[idx++] = (int)i;
        }
    }

    return indices;
}

int main(void) {
    int arr[] = {3, 7, 2, 7, 5, 7, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t count = 0;

    int* indices = find_max_indices(arr, size, &count);

    if (indices != NULL) {
        printf("Maximum value indices: ");
        for (size_t i = 0; i < count; i++) {
            printf("%d ", indices[i]);
        }
        printf("\n");
        free(indices);
    } else {
        printf("No valid indices found.\n");
    }

    return 0;
}