#include <stdio.h>
#include <stdlib.h>

void findMissingRanges(int* nums, int numsSize, int lower, int upper, int*** pReturnSize) {
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > lower) {
            (*pReturnSize)[j] = (int*)malloc(2 * sizeof(int));
            (*pReturnSize)[j][0] = lower;
            (*pReturnSize)[j][1] = nums[i] - 1;
            j++;
        }
        if (nums[i] == upper) {
            return;
        }
        lower = nums[i] + 1;
    }
    if (lower <= upper) {
        (*pReturnSize)[j] = (int*)malloc(2 * sizeof(int));
        (*pReturnSize)[j][0] = lower;
        (*pReturnSize)[j][1] = upper;
    }
}

int main() {
    int nums[] = {0, 1, 3, 50, 75};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int lower = 0, upper = 99;
    int** returnSize = (int**)malloc(numsSize * sizeof(int*));
    for (int i = 0; i < numsSize; i++)
        returnSize[i] = 0;
    findMissingRanges(nums, numsSize, lower, upper, &returnSize);
    for (int i = 0; i < numsSize && returnSize[i] != NULL; i++) {
        printf("[%d, %d]\n", returnSize[i][0], returnSize[i][1]);
        free(returnSize[i]);
    }
    free(returnSize);
    return 0;
}