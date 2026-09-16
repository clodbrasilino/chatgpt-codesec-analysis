#include <stdio.h>
#include <stdlib.h>

int sum_of_negatives(const int *numbers, size_t size) {
    if (numbers == NULL) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; ++i) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }
    
    return sum;
}

int main(void) {
    int nums[] = {3, -1, 4, -5, 9, -2, 6, 0, -8};
    size_t size = sizeof(nums) / sizeof(nums[0]);
    
    int result = sum_of_negatives(nums, size);
    
    printf("Sum of negative numbers: %d\n", result);
    
    const int *null_array = NULL;
    int null_result = sum_of_negatives(null_array, 0);
    
    printf("Sum of null array: %d\n", null_result);
    
    return 0;
}