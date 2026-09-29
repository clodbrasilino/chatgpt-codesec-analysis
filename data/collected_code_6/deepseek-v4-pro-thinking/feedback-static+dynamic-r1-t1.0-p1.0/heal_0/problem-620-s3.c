#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int *largestDivisibleSubset(int *nums, int numsSize, int *returnSize) {
    if (returnSize == NULL) {
        return NULL;
    }

    if (nums == NULL || numsSize <= 0) {
        *returnSize = 0;
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), cmp);

    int *dp = (int *)malloc((size_t)numsSize * sizeof(int));
    int *prev = (int *)malloc((size_t)numsSize * sizeof(int));

    if (dp == NULL || prev == NULL) {
        free(dp);
        free(prev);
        *returnSize = 0;
        return NULL;
    }

    int maxIdx = 0;

    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1;
        prev[i] = -1;

        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }

        if (dp[i] > dp[maxIdx]) {
            maxIdx = i;
        }
    }

    int size = dp[maxIdx];
    int *result = (int *)malloc((size_t)size * sizeof(int));

    if (result == NULL) {
        free(dp);
        free(prev);
        *returnSize = 0;
        return NULL;
    }

    int idx = maxIdx;

    for (int i = size - 1; i >= 0; i--) {
        result[i] = nums[idx];
        idx = prev[idx];
    }

    free(dp);
    free(prev);

    *returnSize = size;
    return result;
}

int main(void) {
    int nums[] = {1, 2, 3, 4, 6, 8};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize = 0;

    int *result = largestDivisibleSubset(nums, numsSize, &returnSize);

    if (result != NULL) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}