#include <stdio.h>
#include <stdlib.h>

int count_sequences(long long arr[], int n, int k, long long dp[51][51][201]) {
    if (n == 0) {
        return k == 0 ? 1 : 0;
    }
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'k+100>=0' is not redundant
     *  Negative array index
     *  Either the condition 'k+100<201' is redundant or the array 'dp[51][51][201]' is accessed at index dp[*][100][*], which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Either the condition 'k+100>=0' is redundant or the array 'dp[51][51][201]' is accessed at index dp[*][-100][*], which is out of bounds. [negativeIndex]
     * UBSan: index 56 out of bounds for type 'long long[51][201]' (AFL crash: id:000000,sig:06,src:000001,time:309,execs:133,op:havoc,rep:4)
     *  Assuming that condition 'k+100<201' is not redundant
     */
    if (k + 100 >= 0 && k + 100 < 201 && dp[n][k][100 + arr[0]] != -1) {
        /* Possible weaknesses found:
         *  Either the condition 'k+100>=0' is redundant or the array 'dp[51][51][201]' is accessed at index dp[*][-100][*], which is out of bounds. [negativeIndex]
         *  Either the condition 'k+100<201' is redundant or the array 'dp[51][51][201]' is accessed at index dp[*][100][*], which is out of bounds. [arrayIndexOutOfBoundsCond]
         *  Array index out of bounds
         *  Negative array index
         */
        return dp[n][k][100 + arr[0]];
    }
    /* Possible weaknesses found:
     *  Assuming that condition 'arr[0]>k' is not redundant
     */
    if (arr[0] > k) {
        dp[n][k][100 + arr[0]] = count_sequences(arr + 1, n - 1, k, dp);
    } else {
        /* Possible weaknesses found:
         *  Condition 'k-arr[0]+100>=0' is always true [knownConditionTrueFalse]
         *  Condition 'k-arr[0]+100>=0' is always true
         */
        if (k - arr[0] + 100 >= 0 && k - arr[0] + 100 < 201) {
            /* Possible weaknesses found:
             * UBSan: index 53 out of bounds for type 'long long[51][201]' (AFL crash: id:000000,sig:06,src:000001,time:309,execs:133,op:havoc,rep:4)
             */
            dp[n][k][100 + arr[0]] = (count_sequences(arr + 1, n - 1, k - arr[0], dp) +
                                     count_sequences(arr + 1, n - 1, k, dp)) % 1000000007;
        }
    }
    /* Possible weaknesses found:
     * UBSan: index 53 out of bounds for type 'long long[51][201]' (AFL crash: id:000000,sig:06,src:000001,time:309,execs:133,op:havoc,rep:4)
     */
    return dp[n][k][100 + arr[0]];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000001,time:1014,execs:280,op:havoc,rep:3; likely memory-safety defect
  */

int main() {
    long long arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k_target;
    printf("Enter the length of the sequence: ");
    if (scanf("%d", &k_target) != 1 || k_target < 0) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

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