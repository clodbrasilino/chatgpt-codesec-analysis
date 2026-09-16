#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_difference(int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return -1; 
    }

    int min_element = arr[0];
    int max_diff = arr[1] - arr[0];

    for (size_t i = 1; i < size; i++) {
        if (arr[i] - min_element > max_diff) {
            max_diff = arr[i] - min_element;
        }
        if (arr[i] < min_element) {
            min_element = arr[i];
        }
    }

    return max_diff;
}

int main(void) {
    int arr[] = {7, 9, 5, 6, 3, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int max_diff = find_max_difference(arr, size);

    if (max_diff != -1) {
        printf("Maximum difference is %d\n", max_diff);
    } else {
        printf("Invalid array size or null pointer\n");
    }

    return 0;
}