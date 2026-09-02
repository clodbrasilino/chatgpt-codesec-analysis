#include <stdio.h>
#include <stdlib.h>

int* find_min_indices(const int *arr, int size, int *count) {
    if (arr == NULL || size <= 0 || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }

    int min_val = arr[0];
    int min_count = 1;

    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_count = 1;
        } else if (arr[i] == min_val) {
            min_count++;
        }
    }

    int *indices = (int *)malloc(min_count * sizeof(int));
    if (indices == NULL) {
        *count = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == min_val) {
            indices[idx++] = i;
        }
    }

    *count = min_count;
    return indices;
}

int main(void) {
    int arr[] = {5, 2, 8, 2, 9, 1, 7, 1, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    int count = 0;

    int *min_indices = find_min_indices(arr, size, &count);

    if (min_indices != NULL) {
        printf("Minimum value indices: ");
        for (int i = 0; i < count; i++) {
            printf("%d", min_indices[i]);
            if (i < count - 1) {
                printf(", ");
            }
        }
        printf("\n");
        free(min_indices);
    } else {
        printf("No minimum indices found or memory allocation failed.\n");
    }

    return 0;
}