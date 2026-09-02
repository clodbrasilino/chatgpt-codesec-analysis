#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'strcmp' is defined in header '<string.h>'; this is probably fixable by adding '#include <string.h>'
  */

int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  include the header <string.h> or explicitly provide a declaration for 'strcmp'
     *  'strcmp' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     *  call to undeclared library function 'strcmp' with type 'int (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    qsort(nums, numsSize, sizeof(int), (int(*)(const void*, const void*))strcmp);
    int *dp = (int*)calloc(numsSize, sizeof(int));
    int *prev = (int*)calloc(numsSize, sizeof(int));
    int maxIndex = 0, maxSize = 1;

    for (int i = 1; i < numsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
                if (dp[i] >= maxSize) {
                    maxSize = dp[i] + 1;
                    maxIndex = i;
                }
            }
        }
    }

    int *result = (int*)malloc(maxSize * sizeof(int));
    *returnSize = maxSize;
    for (int i = maxIndex, j = maxSize - 1; i != -1; i = prev[i], j--) {
        result[j] = nums[i];
    }

    free(dp);
    free(prev);
    return result;
}

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = 3;
    int returnSize;

    int *result = largestDivisibleSubset(nums, numsSize, &returnSize);

    for (int i = 0; i < returnSize; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}