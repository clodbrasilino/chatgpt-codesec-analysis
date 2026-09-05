#include <stdio.h>
#include <stdlib.h>

int* find_max_indices(const int* arr, size_t size, size_t* out_count) {
    if (arr == NULL || out_count == NULL || size == 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    int max_val = arr[0];
    for (size_t i = 1; i < size; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == max_val) {
            ++count;
        }
    }

    if (count == 0) {
        *out_count = 0;
        return NULL;
    }

    int* indices = (int*)malloc(count * sizeof(int));
    if (indices == NULL) {
        *out_count = 0;
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == max_val) {
            indices[idx++] = (int)i;
        }
    }

    *out_count = count;
    return indices;
}

int main(void) {
    int arr[] = {1, 5, 3, 5, 2, 5, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t count = 0;

    int* indices = find_max_indices(arr, size, &count);

    if (indices != NULL && count > 0) {
        printf("Maximum value indices: ");
        for (size_t i = 0; i < count; ++i) {
            printf("%d ", indices[i]);
        }
        printf("\n");
        free(indices);
        indices = NULL;
    } else {
        printf("No maximum values found or invalid input.\n");
    }

    return 0;
}