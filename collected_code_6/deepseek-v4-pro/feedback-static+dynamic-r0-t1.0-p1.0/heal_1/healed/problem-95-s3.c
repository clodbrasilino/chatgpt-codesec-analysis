#include <stdio.h>
#include <stdlib.h>

int min_sublist_length(const int *arr, int size, int target_sum) {
    if (arr == NULL || size <= 0) {
        return -1;
    }
    
    int min_length = size + 1;
    int current_sum = 0;
    int left = 0;
    
    for (int right = 0; right < size; right++) {
        current_sum += arr[right];
        
        while (current_sum >= target_sum && left <= right) {
            int current_length = right - left + 1;
            if (current_length < min_length) {
                min_length = current_length;
            }
            current_sum -= arr[left];
            left++;
        }
    }
    
    if (min_length == size + 1) {
        return 0;
    }
    
    return min_length;
}

int main(int argc, char *argv[]) {
    int test_array[] = {2, 3, 1, 2, 4, 3};
    int target = 7;
    int result = min_sublist_length(test_array, 6, target);
    
    printf("Minimum sublist length: %d\n", result);
    
    int test_array2[] = {1, 1, 1, 1, 1};
    result = min_sublist_length(test_array2, 5, 11);
    printf("No valid sublist result: %d\n", result);
    
    int test_array3[] = {5};
    result = min_sublist_length(test_array3, 1, 5);
    printf("Single element result: %d\n", result);
    
    int *null_array = NULL;
    result = min_sublist_length(null_array, 0, 5);
    printf("Null array result: %d\n", result);
    
    return 0;
}