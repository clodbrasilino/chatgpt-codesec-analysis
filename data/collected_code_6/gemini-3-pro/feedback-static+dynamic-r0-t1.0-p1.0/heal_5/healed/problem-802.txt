#include <stdio.h>
#include <stdlib.h>

int countRotations(const int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_idx]) {
            min_idx = i;
        }
    }

    return min_idx;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }

    int rotations = countRotations(arr, n);
    
    if (rotations != -1) {
        printf("%d\n", rotations);
    }

    free(arr);
    return EXIT_SUCCESS;
}