#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_difference(const int *arr, size_t size, int *difference) {
    if (arr == NULL || difference == NULL || size == 0) {
        return -1;
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (size_t i = 0; i < size; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    if (max_val >= 0 && min_val < 0 && max_val > INT_MAX + min_val) {
        return -2;
    }
    
    *difference = max_val - min_val;
    return 0;
}

int main(void) {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int difference;

    if (find_difference(arr, size, &difference) == 0) {
        printf("Difference: %d\n", difference);
    } else {
        printf("Error calculating difference.\n");
    }

    return 0;
}