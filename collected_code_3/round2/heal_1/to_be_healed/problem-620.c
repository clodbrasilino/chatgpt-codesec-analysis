#include <stdio.h>
#include <stdlib.h>

int largestDivisibleSubset(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    int *count = (int*)malloc(sizeof(int)*numsSize);
    int *pre = (int*)malloc(sizeof(int)*numsSize);
    int max = 0, index = -1;
    for (int i = 0; i < numsSize; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'count' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        count[i] = 1;
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'pre' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        pre[i] = -1;
        for (int j = i - 1; j >= 0; j--) {
            if (nums[i] % nums[j] == 0) {
                if (1 + count[j] > count[i]) {
                    count[i] = count[j] + 1;
                    pre[i] = j;
                }
            }
        }
        if (count[i] > max) {
            max = count[i];
            index = i;
        }
    }
    /* Possible weaknesses found:
     *  leak of 'pre' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of 'count' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return max;
}

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int result = largestDivisibleSubset(nums, numsSize);
    printf("The largest subset where each pair is divisible is: %d\n", result);
    return 0;
}