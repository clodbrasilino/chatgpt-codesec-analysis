#include <stdio.h>
#include <stdlib.h>

int findFirstMissingPositive(int* nums, int numsSize) {
    if (nums == NULL || numsSize <= 0) {
        return 1;
    }

    for (int i = 0; i < numsSize; i++) {
        while (nums[i] > 0 && nums[i] <= numsSize && nums[nums[i] - 1] != nums[i]) {
            int temp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = temp;
        }
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    return numsSize + 1;
}

int main() {
    int nums[] = {3, 4, -1, 1};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = findFirstMissingPositive(nums, numsSize);
    printf("%d\n", result);

    int nums2[] = {1, 2, 0};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);

    int result2 = findFirstMissingPositive(nums2, numsSize2);
    printf("%d\n", result2);

    int nums3[] = {7, 8, 9, 11, 12};
    int numsSize3 = sizeof(nums3) / sizeof(nums3[0]);

    int result3 = findFirstMissingPositive(nums3, numsSize3);
    printf("%d\n", result3);

    return 0;
}