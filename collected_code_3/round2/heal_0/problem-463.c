#include <stdio.h>
#include <limits.h>

int maxProduct(int* nums, int numsSize) {
    int max = nums[0], min = nums[0], result = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < 0) {
            int temp = max;
            max = min;
            min = temp;
        }
        max = (nums[i] > max * nums[i]) ? nums[i] : max * nums[i];
        min = (nums[i] < min * nums[i]) ? nums[i] : min * nums[i];
        result = (result > max) ? result : max;
    }
    return result;
}

int main() {
    int nums[] = {2, 3, -2, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int maxProductSubarray = maxProduct(nums, numsSize);
    printf("Maximum product subarray is %d\n", maxProductSubarray);
    return 0;
}