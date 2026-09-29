#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
int* findLargestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int *dp = (int *)malloc(numsSize * sizeof(int));
    int *parent = (int *)malloc(numsSize * sizeof(int));
    int maxIndex = 0;

    for (int i = 0; i < numsSize; ++i) {
        dp[i] = 1;
        parent[i] = -1;
    }

    for (int i = 1; i < numsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] % nums[j] == 0 && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > dp[maxIndex]) {
            maxIndex = i;
        }
    }

    int *result = (int *)malloc((dp[maxIndex] + 1) * sizeof(int));
    result[dp[maxIndex]] = -1;
    int index = dp[maxIndex] - 1;
    while (maxIndex != -1) {
        result[index--] = nums[maxIndex];
        maxIndex = parent[maxIndex];
    }

    /* Possible weaknesses found:
     * ASan: heap-buffer-overflow
     */
    *returnSize = dp[maxIndex];
    free(dp);
    free(parent);

    return result;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int nums[] = {1, 2, 3, 4, 6, 8};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    qsort(nums, numsSize, sizeof(int), compare);

    int returnSize;
    int *result = findLargestDivisibleSubset(nums, numsSize, &returnSize);

    for (int i = 0; i < returnSize; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);

    return 0;
}