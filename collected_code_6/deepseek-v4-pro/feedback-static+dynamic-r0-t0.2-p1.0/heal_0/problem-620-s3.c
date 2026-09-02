#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), cmp);

    int *dp = (int*)malloc(numsSize * sizeof(int));
    int *prev = (int*)malloc(numsSize * sizeof(int));
    int *result = NULL;

    if (dp == NULL || prev == NULL) {
        free(dp);
        free(prev);
        *returnSize = 0;
        return NULL;
    }

    int maxIndex = 0;
    int maxSize = 1;

    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }
        if (dp[i] > maxSize) {
            maxSize = dp[i];
            maxIndex = i;
        }
    }

    *returnSize = maxSize;
    result = (int*)malloc(maxSize * sizeof(int));
    if (result == NULL) {
        free(dp);
        free(prev);
        *returnSize = 0;
        return NULL;
    }

    int idx = maxSize - 1;
    int current = maxIndex;
    while (current != -1) {
        result[idx--] = nums[current];
        current = prev[current];
    }

    free(dp);
    free(prev);
    return result;
}

int main() {
    int nums[] = {1, 2, 4, 8};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize = 0;

    int *result = largestDivisibleSubset(nums, numsSize, &returnSize);

    printf("Largest Divisible Subset: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}