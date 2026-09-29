#include <stdio.h>
#include <stdlib.h>

int* remove_negatives(int *arr, int n, int *new_size) {
    int *result = NULL;
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 0) {
            result = realloc(result, (count + 1) * sizeof(int));
            if (result == NULL) {
                free(result);
                return NULL;
            }
            result[count++] = arr[i];
        }
    }

    *new_size = count;
    return result;
}

int main() {
    int arr[] = {-2, 3, -5, 4, 6, -7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int new_size;

    int *result = remove_negatives(arr, n, &new_size);

    if (result != NULL) {
        for (int i = 0; i < new_size; ++i) {
            printf("%d ", result[i]);
        }
        free(result);
    } else {
        printf("Memory allocation failed\n");
    }

    return 0;
}