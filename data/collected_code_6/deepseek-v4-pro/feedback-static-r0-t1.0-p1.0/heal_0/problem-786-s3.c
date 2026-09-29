#include <stdio.h>
#include <stdlib.h>

int find_insertion_point(const int *arr, size_t len, int value) {
    size_t left = 0;
    size_t right = len;
    
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
    size_t len = sizeof(arr) / sizeof(arr[0]);
    
    int values_to_test[] = {0, 1, 2, 7, 8, 13, 14};
    size_t num_tests = sizeof(values_to_test) / sizeof(values_to_test[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        int pos = find_insertion_point(arr, len, values_to_test[i]);
        printf("Insertion point for %d: %d\n", values_to_test[i], pos);
    }
    
    return EXIT_SUCCESS;
}