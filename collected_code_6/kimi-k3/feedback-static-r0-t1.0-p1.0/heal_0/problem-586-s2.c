#include <stdio.h>
#include <stdlib.h>

int* rotateArray(int arr[], int n, int k) {
    if (arr == NULL || n <= 0 || k < 0 || k >= n) {
        return NULL;
    }
    
    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        result[i] = arr[(i + k) % n];
    }
    
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    
    int* result = rotateArray(arr, n, k);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Invalid input or memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("Rotated array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    result = NULL;
    
    return EXIT_SUCCESS;
}