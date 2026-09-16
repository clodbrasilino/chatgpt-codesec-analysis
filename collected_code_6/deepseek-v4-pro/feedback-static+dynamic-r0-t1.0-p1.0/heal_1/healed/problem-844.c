#include <stdio.h>
#include <stdlib.h>

int find_kth_element(const int *arr, int size, int k) {
    if (arr == NULL || size <= 0 || k < 0 || k >= size) {
        fprintf(stderr, "Invalid input parameters\n");
        exit(EXIT_FAILURE);
    }

    int *temp = (int *)malloc(size * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            temp[index++] = arr[i];
        }
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            temp[index++] = arr[i];
        }
    }

    int result = temp[k];
    free(temp);

    return result;
}

int main(void) {
    int arr[] = {3, 5, 2, 8, 7, 4, 1, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 3;

    int result = find_kth_element(arr, size, k);
    printf("Element at index %d: %d\n", k, result);

    return 0;
}