#include <stdio.h>
#include <limits.h>

int sum_largest_smallest(int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int min_val = array[0];
    int max_val = array[0];

    for (size_t i = 1; i < size; i++) {
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
    int arr[] = {10, 3, 5, 1, 8, 9, 2};
    size_t arr_size = sizeof(arr) / sizeof(arr[0]);

    int result = sum_largest_smallest(arr, arr_size);
    printf("%d\n", result);

    return 0;
}