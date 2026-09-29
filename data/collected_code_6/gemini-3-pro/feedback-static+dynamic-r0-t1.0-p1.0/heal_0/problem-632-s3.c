#include <stdio.h>
#include <stdlib.h>

void moveZeroes(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 0) {
        return;
    }

    int nonZeroIndex = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            nums[nonZeroIndex] = nums[i];
            nonZeroIndex++;
        }
    }

    for (int i = nonZeroIndex; i < numsSize; i++) {
        nums[i] = 0;
    }
}

int main(void) {
    int nums[] = {0, 1, 0, 3, 12};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    moveZeroes(nums, numsSize);

    for (int i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}