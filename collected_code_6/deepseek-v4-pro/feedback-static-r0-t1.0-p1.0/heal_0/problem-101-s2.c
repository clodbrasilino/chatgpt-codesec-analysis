#include <stdio.h>
#include <stdlib.h>

int find_kth_element(int *arr, int size, int k) {
    if (arr == NULL || size <= 0 || k < 0 || k >= size) {
        fprintf(stderr, "Invalid input parameters\n");
        exit(EXIT_FAILURE);
    }
    return arr[k];
}

int main(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int result = find_kth_element(arr, size, k);
    printf("Element at index %d: %d\n", k, result);
    return 0;
}