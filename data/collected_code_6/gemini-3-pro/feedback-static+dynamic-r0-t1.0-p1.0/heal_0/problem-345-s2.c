#include <stdio.h>
#include <stdlib.h>

int* find_differences(const int* arr, size_t size, size_t* diff_size) {
    if (arr == NULL || diff_size == NULL || size < 2) {
        if (diff_size != NULL) {
            *diff_size = 0;
        }
        return NULL;
    }

    *diff_size = size - 1;
    int* diff_arr = (int*)malloc((*diff_size) * sizeof(int));
    if (diff_arr == NULL) {
        *diff_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *diff_size; ++i) {
        diff_arr[i] = arr[i + 1] - arr[i];
    }

    return diff_arr;
}

int main(void) {
    int arr[] = {10, 15, 23, 17, 30};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t diff_size = 0;

    int* diffs = find_differences(arr, size, &diff_size);

    if (diffs != NULL) {
        for (size_t i = 0; i < diff_size; ++i) {
            printf("%d ", diffs[i]);
        }
        printf("\n");
        free(diffs);
    } else {
        printf("Failed to compute differences or array too small.\n");
    }

    return 0;
}