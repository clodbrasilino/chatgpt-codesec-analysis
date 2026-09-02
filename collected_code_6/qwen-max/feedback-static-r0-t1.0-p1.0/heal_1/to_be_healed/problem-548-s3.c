#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'nums' can be declared as pointer to const [constParameterPointer]
 */
int lengthOfLIS(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    int* dp = (int*)malloc(numsSize * sizeof(int));
    if (dp == NULL) exit(1);
    dp[0] = nums[0];
    int len = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > dp[len - 1]) {
            dp[len++] = nums[i];
        } else {
            int index = 0;
            while (dp[index] < nums[i]) index++;
            dp[index] = nums[i];
        }
    }
    free(dp);
    return len;
}

int main() {
    int arr[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of the longest increasing subsequence: %d\n", lengthOfLIS(arr, n));
    return 0;
}