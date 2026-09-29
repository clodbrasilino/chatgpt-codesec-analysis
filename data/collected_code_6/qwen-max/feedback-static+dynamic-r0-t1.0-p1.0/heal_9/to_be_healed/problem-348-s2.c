#include <stdio.h>
#include <stdlib.h>

int count_sequences(long long arr[], int n, int k, long long dp[51][51][201]) {
    if (n == 0) {
        return k == 0 ? 1 : 0;
    }
    int index = 100 + arr[0];
    /* Possible weaknesses found:
     * UBSan: index -1 out of bounds for type 'long long[51][201]' (AFL crash: id:000001,sig:06,src:000000,time:190,execs:224,op:havoc,rep:1)
     */
    if (index >= 0 && index < 201 && dp[n-1][k][index] != -1) {
        /* Possible weaknesses found:
         * UBSan: index -1 out of bounds for type 'long long[51][201]' (AFL crash: id:000001,sig:06,src:000000,time:190,execs:224,op:havoc,rep:1)
         */
        return dp[n-1][k][index];
    }
    if (arr[0] > k) {
        dp[n-1][k][index] = count_sequences(arr + 1, n - 1, k, dp);
    } else {
        dp[n-1][k][index] = (count_sequences(arr + 1, n - 1, k - arr[0], dp) + 
                          count_sequences(arr + 1, n - 1, k, dp)) % 1000000007;
    }
    return dp[n-1][k][index];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:130,execs:157,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    long long arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k;
    printf("Enter the value of k: ");
    if (scanf("%d", &k) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    long long dp[51][51][201];
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j <= k && j < 51; ++j) {
            for (int m = 0; m < 201; ++m) {
                dp[i][j][m] = -1;
            }
        }
    }

    int result = count_sequences(arr, n, k, dp);
    printf("Total sequences: %d\n", result);

    return 0;
}