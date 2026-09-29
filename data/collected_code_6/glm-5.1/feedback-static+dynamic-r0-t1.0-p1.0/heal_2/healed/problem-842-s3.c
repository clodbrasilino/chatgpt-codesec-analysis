#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(const int *arr, size_t size) {
    if (size == 0) {
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

    int odd_number = find_odd_occurrence(arr, size);
    if (odd_number == -1) {
        return EXIT_FAILURE;
    }
    printf("%d\n", odd_number);

    return EXIT_SUCCESS;
}