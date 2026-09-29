#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define ARRAY_SIZE 10

int locate_insertion_point(const int *arr, size_t size, int value)
{
    size_t left;
    size_t right;
    
    if (arr == NULL) {
        return -1;
    }
    
    left = 0;
    right = size;
    
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        
        if (arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    if (left > (size_t)INT_MAX) {
        return -1;
    }
    
    return (int)left;
}

int main(void)
{
    const int sorted_array[ARRAY_SIZE] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int test_values[] = {0, 5, 10, 20, 1, 19};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    size_t i;
    int result;
    
    for (i = 0; i < num_tests; i++) {
        result = locate_insertion_point(sorted_array, ARRAY_SIZE, test_values[i]);
        
        if (result < 0) {
            fprintf(stderr, "Error: Invalid input parameters\n");
            return EXIT_FAILURE;
        }
        
        printf("Value %d should be inserted at index %d\n", test_values[i], result);
    }
    
    result = locate_insertion_point(NULL, ARRAY_SIZE, 5);
    if (result < 0) {
        printf("NULL array test: Correctly returned error\n");
    }
    
    return EXIT_SUCCESS;
}