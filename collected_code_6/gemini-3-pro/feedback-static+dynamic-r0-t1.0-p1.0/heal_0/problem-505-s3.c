#include <stdio.h>
#include <stddef.h>

void moveZeroes(int* nums, size_t numsSize) {
    if (nums == NULL || numsSize == 0) {
        return;
    }

    size_t lastNonZeroFoundAt = 0;

    for (size_t i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            nums[lastNonZeroFoundAt++] = nums[i];
        }
    }

    for (size_t i = lastNonZeroFoundAt; i < numsSize; i++) {
        nums[i] = 0;
    }
}

int main(void) {
    int nums[] = {0, 1, 0, 3, 12};
    size_t numsSize = sizeof(nums) / sizeof(nums[0]);

    moveZeroes(nums, numsSize);

    for (size_t i = 0; i < numsSize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}