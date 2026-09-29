#include <stdio.h>
#include <stdlib.h>

int count_sequences(long long arr[], int n, int k, long long dp[51][51][201]) {
    if (n == 0) {
        return k == 0 ? 1 : 0;
    }
    if (dp[n][k][100 + arr[0]] != -1) {
        return dp[n][k][100 + arr[0]];
    }
    if (arr[0] > k) {
        return dp[n][k][100 + arr[0]] = count_sequences(arr + 1, n - 1, k, dp);
    } else {
        return dp[n][k][100 + arr[0]] = (count_sequences(arr + 1, n - 1, k - arr[0], dp) + 
                                        count_sequences(arr + 1, n - 1, k, dp)) % 1000000007;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:420,execs:65,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    long long arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k_target;
    printf("Enter the length of the sequence: ");
    scanf("%d", &k_target);

    long long dp[51][51][201];
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 51; ++j) {
            for (int k = 0; k < 201; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }

    int result = count_sequences(arr, n, k_target, dp);
    printf("Total sequences: %d\n", result);

    return 0;
}