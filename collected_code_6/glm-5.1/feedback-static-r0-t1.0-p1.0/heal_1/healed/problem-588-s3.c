#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_difference(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (size_t i = 0; i < size; ++i) {
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
    int arr1[] = {10, 3, 5, 6, 20};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_difference(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {-10, -3, -5, -6, -20};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_difference(arr2, size2);
    printf("%d\n", result2);

    int result3 = find_difference(NULL, 5);
    printf("%d\n", result3);

    int empty_arr[] = {};
    size_t size_empty = 0;
    int result4 = find_difference(empty_arr, size_empty);
    printf("%d\n", result4);

    return 0;
}