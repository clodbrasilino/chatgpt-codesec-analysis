#include <stdio.h>
#include <stdbool.h>

bool containsDuplicate(int* nums, int numsSize){
    for(int i = 0; i < numsSize; ++i) {
        for(int j = i + 1; j < numsSize; ++j) {
            if(nums[i] == nums[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    if(containsDuplicate(nums, numsSize)) {
        printf("Array contains duplicate elements.\n");
    } else {
        printf("Array does not contain duplicate elements.\n");
    }

    return 0;
}