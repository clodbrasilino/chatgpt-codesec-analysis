#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 2, got <no output>
  *  test case 2 failed: expected 3, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  */

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

int main(int argc, char* const* argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num1> <num2> ...\n", argv[0]);
        return 1;
    }

    int numsSize = argc - 1;
    int* nums = (int*)malloc(numsSize * sizeof(int));
    if (nums == NULL) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < numsSize; i++) {
        char* endptr;
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(nums);
            return 1;
        }
        nums[i] = (int)val;
    }

    int missing = firstMissingPositive(nums, numsSize);
    printf("%d\n", missing);

    free(nums);

    return 0;
}