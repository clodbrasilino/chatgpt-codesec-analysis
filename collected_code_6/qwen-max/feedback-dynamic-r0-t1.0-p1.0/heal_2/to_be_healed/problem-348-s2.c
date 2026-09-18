#include <stdio.h>
#include <stdlib.h>

int count_sequences(long long arr[], int n, int k, long long dp[51][51][201]) {
    if (n == 0) {
        return k == 0 ? 1 : 0;
    }
    /* Possible weaknesses found:
     * UBSan: index 66 out of bounds for type 'long long[51][201]' (AFL crash: id:000000,sig:06,src:000002,time:3201,execs:442,op:havoc,rep:4)
     */
    if (dp[n][k][100 + arr[0]] != -1) {
        return dp[n][k][100 + arr[0]];
    }
    if (arr[0] > k) {
        return dp[n][k][100 + arr[0]] = count_sequences(arr + 1, n - 1, k, dp);
    } else {
        /* Possible weaknesses found:
         * UBSan: index 63 out of bounds for type 'long long[51][201]' (AFL crash: id:000000,sig:06,src:000002,time:3201,execs:442,op:havoc,rep:4)
         */
        return dp[n][k][100 + arr[0]] = (count_sequences(arr + 1, n - 1, k - arr[0], dp) + 
                                        count_sequences(arr + 1, n - 1, k, dp)) % 1000000007;
    }
}

int main() {
    long long arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k;
    printf("Enter the value of k: ");
    scanf("%d", &k);

    if (k < 0 || k > 100) {
        fprintf(stderr, "k must be between 0 and 100\n");
        return 1;
    }

    long long dp[51][51][201];
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 51; ++j) {
            for (int l = 0; l < 201; ++l) {
                dp[i][j][l] = -1;
            }
        }
    }

    int result = count_sequences(arr, n, k, dp);
    printf("Total sequences: %d\n", result);

    return 0;
}