#include <stdio.h>
#include <limits.h>

int find_difference(const int *array, size_t size) {
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

    return max_val - min_val;
}

int main(void) {
    int arr[] = {10, 3, 5, 6, 20};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int result = find_difference(arr, size);
    printf("%d\n", result);

    return 0;
}