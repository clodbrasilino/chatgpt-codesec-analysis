#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 27, got <no output>
  *  test case 1 failed: expected 5013, got <no output>
  *  test case 0 failed: expected 2101, got <no output>
  */

int max_sum_no_three_consecutive(int arr[], int n) {
    if (n == 0) return 0;
    if (n == 1) return arr[0];
    if (n == 2) return arr[0] + arr[1];

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = arr[0];
    dp[1] = arr[0] + arr[1];
    
    int max2 = arr[1] + arr[2];
    int max3 = arr[0] + arr[2];
    dp[2] = (dp[1] > max2) ? dp[1] : max2;
    dp[2] = (dp[2] > max3) ? dp[2] : max3;

    for (int i = 3; i < n; i++) {
        int opt1 = dp[i-1];
        int opt2 = dp[i-2] + arr[i];
        int opt3 = dp[i-3] + arr[i-1] + arr[i];

        int max_val = (opt1 > opt2) ? opt1 : opt2;
        max_val = (max_val > opt3) ? max_val : opt3;
        
        dp[i] = max_val;
    }

    int result = dp[n-1];
    free(dp);
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    int max_sum = max_sum_no_three_consecutive(arr, n);
    if (max_sum != -1) {
        printf("%d\n", max_sum);
    }

    return 0;
}