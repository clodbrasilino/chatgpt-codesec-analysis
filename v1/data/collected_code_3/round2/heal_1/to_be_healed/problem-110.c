#include <stdio.h>
#include <stdlib.h>

void findMissingRanges(int* nums, int numsSize, int lower, int upper, int** returnSize) {
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > lower) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'returnSize' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            returnSize[j] = (int*)malloc(2 * sizeof(int));
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*returnSize' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  dereference of possibly-NULL '*returnSize_57(D) + _10' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            returnSize[j][0] = lower;
            returnSize[j][1] = nums[i] - 1;
            j++;
        }
        if (nums[i] == upper) {
            return;
        }
        lower = nums[i] + 1;
    }
    if (lower <= upper) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'returnSize' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        returnSize[j] = (int*)malloc(2 * sizeof(int));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*returnSize_57(D) + _36' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        returnSize[j][0] = lower;
        returnSize[j][1] = upper;
    }
}

int main() {
    int nums[] = {0, 1, 3, 50, 75};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int lower = 0, upper = 99;
    int** returnSize = (int**)malloc(numsSize * sizeof(int*));
    findMissingRanges(nums, numsSize, lower, upper, returnSize);
    /* Possible weaknesses found:
     *  use of uninitialized value '*returnSize_34 + _19' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     *  dereference of possibly-NULL 'returnSize' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    for (int i = 0; i < numsSize && returnSize[i] != NULL; i++) {
        printf("[%d, %d]\n", returnSize[i][0], returnSize[i][1]);
        free(returnSize[i]);
    }
    free(returnSize);
    return 0;
}