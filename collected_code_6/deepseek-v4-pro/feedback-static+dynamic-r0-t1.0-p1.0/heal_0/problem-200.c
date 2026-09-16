#include <stdio.h>
#include <stdlib.h>

int* find_max_indices(const int *arr, int size, int *count) {
    if (arr == NULL || size <= 0 || count == NULL) {
        return NULL;
    }

    int max = arr[0];
    int max_count = 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
            max_count = 1;
        } else if (arr[i] == max) {
            max_count++;
        }
    }

    int *indices = (int*)malloc(max_count * sizeof(int));
    if (indices == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == max) {
            indices[index++] = i;
        }
    }

    *count = max_count;
    return indices;
}

int main(void) {
    int arr[] = {3, 5, 2, 5, 7, 5, 7, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int count = 0;

    int *indices = find_max_indices(arr, size, &count);

    if (indices != NULL) {
        printf("Maximum value indices: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", indices[i]);
        }
        printf("\n");
        free(indices);
    } else {
        printf("Error: Unable to find maximum indices or memory allocation failed.\n");
        return 1;
    }

    return 0;
}