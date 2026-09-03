#include <stdio.h>
#include <stdlib.h>

int* remove_negatives(int *arr, int n, int *new_size) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 0) {
            ++count;
        }
    }

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) {
        *new_size = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] >= 0) {
            result[index++] = arr[i];
        }
    }

    *new_size = count;
    return result;
}

int main() {
    int arr[] = {-1, 2, -3, 4, -5, 6};
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