#include <stdbool.h>
#include <stdio.h>

bool isMonotonic(int* nums, int numsSize) {
    bool inc = true;
    bool dec = true;
    
    for (int i = 0; i < numsSize - 1; ++i) {
        if (nums[i] > nums[i + 1])
            inc = false;
        if (nums[i] < nums[i + 1])
            dec = false;
    }
    
    return inc || dec;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    
    if (isMonotonic(nums, numsSize))
        printf("The array is monotonic.\n");
    else
        printf("The array is not monotonic.\n");
    
    return 0;
}