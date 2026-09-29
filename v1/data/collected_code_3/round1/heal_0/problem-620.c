#include <stdio.h>
#include <stdlib.h>

int largestDivisibleSubset(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    int dp[numsSize];
    int max = 1;
    int i, j;
    for (i = 0; i < numsSize; i++) dp[i] = 1;
    qsort(nums, numsSize, sizeof(int), (__compar_fn_t)abs);
    for (i = 1; i < numsSize; i++) {
        for (j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0) {
                dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
            }
        }
        max = max > dp[i] ? max : dp[i];
    }
    return max;
}

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int result = largestDivisibleSubset(nums, numsSize);
    printf("The largest subset where each pair is divisible is: %d\n", result);
    return 0;
}