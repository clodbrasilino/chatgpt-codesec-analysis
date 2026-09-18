#include <stdio.h>
#include <stdlib.h>

int lengthOfLIS(const int *nums, size_t numsSize) {
    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    int *tails = (int *)malloc(numsSize * sizeof(int));
    if (tails == NULL) {
        return -1;
    }

    size_t len = 0;

    for (size_t i = 0; i < numsSize; i++) {
        size_t left = 0;
        size_t right = len;

        while (left < right) {
            size_t mid = left + (right - left) / 2;
            if (tails[mid] < nums[i]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        tails[left] = nums[i];
        if (left == len) {
            len++;
        }
    }

    free(tails);
    return (int)len;
}

int main(void) {
    int nums[] = {10, 9, 2, 5, 3, 7, 101, 18};
    size_t numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = lengthOfLIS(nums, numsSize);
    
    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return EXIT_SUCCESS;
}