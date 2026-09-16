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

int main(void) {
    int arr[] = {3, 4, -1, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int missing = findFirstMissingPositive(arr, size);
    printf("%d\n", missing);
    return 0;
}