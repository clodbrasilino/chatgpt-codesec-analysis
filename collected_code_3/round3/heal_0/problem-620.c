#include <stdio.h>
#include <stdlib.h>

int largestDivisibleSubset(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    int dp[numsSize];
    int max = 1;
    int maxIndex = 0;
    qsort(nums, numsSize, sizeof(int), cmpfunc);
    for (int i = 0; i < numsSize; i++) dp[i] = 1;
    for (int i = 1; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0) {
                dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
            }
        }
        if (dp[i] > max) {
            max = dp[i];
            maxIndex = i;
        }
    }
    return max;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int result = largestDivisibleSubset(nums, numsSize);
    printf("The largest subset where each pair is divisible is: %d\n", result);
    return 0;
}