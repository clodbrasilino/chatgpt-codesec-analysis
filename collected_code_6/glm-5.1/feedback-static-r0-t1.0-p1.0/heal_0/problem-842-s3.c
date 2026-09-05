#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(int *arr, size_t size) {
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        result ^= arr[i];
    }
    return result;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 3, 1, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    if (size == 0) {
        return EXIT_FAILURE;
    }

    int odd_number = find_odd_occurrence(arr, size);
    printf("%d\n", odd_number);

    return EXIT_SUCCESS;
}