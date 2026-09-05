#include <stdio.h>

void moveZeroes(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 0) {
        return;
    }
    
    int insertPos = 0;
    int i;
    
    for (i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            nums[insertPos] = nums[i];
            insertPos++;
        }
    }
    
    while (insertPos < numsSize) {
        nums[insertPos] = 0;
        insertPos++;
    }
}

int main(void) {
    int nums[] = {0, 1, 0, 3, 12};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int i;
    
    moveZeroes(nums, numsSize);
    
    for (i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
    
    return 0;
}