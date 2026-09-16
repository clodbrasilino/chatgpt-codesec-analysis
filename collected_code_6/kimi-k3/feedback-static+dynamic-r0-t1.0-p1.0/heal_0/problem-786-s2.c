#include <stdio.h>
#include <stdlib.h>

int find_insertion_point(const int *arr, size_t size, int value) {
    size_t left = 0;
    size_t right = size;
    
    if (arr == NULL) {
        return -1;
    }
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return (int)left;
}

int main(void) {
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int value = 6;
    
    int pos = find_insertion_point(arr, size, value);
    
    if (pos >= 0) {
        printf("Insertion point for %d: index %d\n", value, pos);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}