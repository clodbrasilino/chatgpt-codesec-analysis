#include <stdio.h>
#include <stdlib.h>

int* removeOdd(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));

    if (result == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            result[j++] = nums[i];
        }
    }
    *returnSize = j;

    result = realloc(result, j * sizeof(int));

    if (result == NULL) {
        *returnSize = 0;
    }
    
    /* Possible weaknesses found:
     *  leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return result;
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* result = removeOdd(nums, numsSize, &returnSize);

    if(result == NULL) return -1;

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}