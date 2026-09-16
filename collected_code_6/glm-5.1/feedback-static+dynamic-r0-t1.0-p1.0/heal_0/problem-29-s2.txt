#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1;
    }
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 3, 1, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int odd_element = find_odd_occurrence(arr, size);
    if (odd_element == -1) {
        return EXIT_FAILURE;
    }
    printf("%d\n", odd_element);
    return EXIT_SUCCESS;
}