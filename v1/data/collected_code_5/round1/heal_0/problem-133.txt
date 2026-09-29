#include <stdio.h>

int sum_of_negative(int* nums, int length) {
    int sum = 0;
    for(int i = 0; i < length; i++) {
        if(nums[i] < 0) {
            sum += nums[i];
        }
    }
    return sum;
}

int main(void) {
    int nums[] = {0, -1, 2, -3, 4, -5, 6};
    printf("Sum of negative numbers: %d\n", sum_of_negative(nums, sizeof(nums) / sizeof(int)));   
    return 0;
}