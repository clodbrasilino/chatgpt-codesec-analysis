#include <stdio.h>
#include <limits.h>

int sum_largest_smallest(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (size_t i = 0; i < size; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }

    return min_val + max_val;
}

int main(void) {
    int arr[] = {10, 3, 5, 1, 9, 8};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int result = sum_largest_smallest(arr, n);
    printf("%d\n", result);

    return 0;
}