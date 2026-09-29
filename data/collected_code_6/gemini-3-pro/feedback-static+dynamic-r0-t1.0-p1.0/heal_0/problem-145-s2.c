#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_difference(const int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return -1; 
    }

    int min_element = arr[0];
    int max_difference = arr[1] - arr[0];

    for (size_t i = 1; i < size; ++i) {
        if (arr[i] - min_element > max_difference) {
            max_difference = arr[i] - min_element;
        }
        if (arr[i] < min_element) {
            min_element = arr[i];
        }
    }

    return max_difference;
}

int main(void) {
    int arr[] = {2, 3, 10, 6, 4, 8, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int max_diff = find_max_difference(arr, size);

    if (max_diff != -1) {
        printf("Maximum difference is %d\n", max_diff);
    } else {
        printf("Invalid input array\n");
    }

    return 0;
}