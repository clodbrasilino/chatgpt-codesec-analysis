#include <stdio.h>
#include <stdlib.h>

int firstMissingPositive(int* nums, int numsSize) {
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

int main(int argc, char* const argv[]) {
    if (argc < 2) {
        return 1;
    }

    int numsSize = argc - 1;
    int* nums = (int*)malloc(numsSize * sizeof(int));
    if (nums == NULL) {
        return 1;
    }

    for (int i = 0; i < numsSize; i++) {
        char* endptr;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (*endptr != '\0' || val > 2147483647 || val < -2147483648) {
            free(nums);
            return 1;
        }
        nums[i] = (int)val;
    }

    int result = firstMissingPositive(nums, numsSize);
    printf("%d\n", result);

    free(nums);
    return 0;
}