#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_second_smallest(const int *arr, size_t size, int *result) {
    if (arr == NULL || result == NULL || size < 2) {
        return -1;
    }
    
    int smallest = INT_MAX;
    int second_smallest = INT_MAX;
    int found_second = 0;
    
    for (size_t i = 0; i < size; i++) {
        if (arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
            found_second = 1;
        } else if (arr[i] > smallest && arr[i] < second_smallest) {
            second_smallest = arr[i];
            found_second = 1;
        }
    }
    
    if (!found_second || second_smallest == INT_MAX) {
        return -1;
    }
    
    *result = second_smallest;
    return 0;
}

int main(void) {
    int arr[] = {12, 13, 1, 10, 34, 1};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;
    
    if (find_second_smallest(arr, size, &result) == 0) {
        printf("Second smallest: %d\n", result);
    } else {
        printf("No second smallest element found\n");
    }
    
    return 0;
}