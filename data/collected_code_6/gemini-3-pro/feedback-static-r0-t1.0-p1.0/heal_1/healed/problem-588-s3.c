#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int findDifference(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return -1; 
    }

    int min_val = INT_MAX;
    int max_val = INT_MIN;

    for (size_t i = 0; i < size; ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    if (max_val >= 0 && min_val < 0) {
        if (max_val > INT_MAX + min_val) {
            return -1; 
        }
    }
    
    return max_val - min_val;
}

int main(int argc, char **argv) {
    int arr[] = { 10, 5, 20, 2, 8 };
    size_t size = sizeof(arr) / sizeof(arr[0]);

    int difference = findDifference(arr, size);
    
    if (difference != -1) {
        printf("Difference: %d\n", difference);
    } else {
        printf("Error calculates difference.\n");
    }

    const int *empty_arr = NULL;
    size_t empty_size = (argc > 100) ? 1 : 0; 
    
    difference = findDifference(empty_arr, empty_size);
    
    if (difference != -1) {
        printf("Difference: %d\n", difference);
    } else {
        printf("Error calculates difference.\n");
    }

    return EXIT_SUCCESS;
}