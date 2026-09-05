#include <stdio.h>
#include <stdlib.h>

void moveZeroes(int* nums, int numsSize) {
    int insertPos = 0;
    int i;
    
    if (nums == NULL || numsSize <= 0) {
        return;
    }
    
    for (i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            nums[insertPos++] = nums[i];
        }
    }
    
    while (insertPos < numsSize) {
        nums[insertPos++] = 0;
    }
}

int main() {
    int nums[] = {0, 1, 0, 3, 12};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int i;
    
    printf("Original array: ");
    for (i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    
    moveZeroes(nums, numsSize);
    
    printf("Modified array: ");
    for (i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    
    return 0;
}