#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    qsort(nums, numsSize, sizeof(int), compare);
    int *dp = (int *)malloc(numsSize * sizeof(int));
    int *parent = (int *)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        dp[i] = 1;
        parent[i] = -1;
    }
    int maxSize = 1;
    int maxIndex = 0;
    for (int i = 1; i < numsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > maxSize) {
            maxSize = dp[i];
            maxIndex = i;
        }
    }
    *returnSize = maxSize;
    int *result = (int *)malloc(maxSize * sizeof(int));
    for (int i = maxSize - 1; i >= 0; --i) {
        result[i] = nums[maxIndex];
        maxIndex = parent[maxIndex];
    }
    free(dp);
    free(parent);
    return result;
}

int main() {
    int nums[] = {1, 2, 3, 4, 6, 8, 9, 12};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int *result = largestDivisibleSubset(nums, numsSize, &returnSize);
    for (int i = 0; i < returnSize; ++i) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}