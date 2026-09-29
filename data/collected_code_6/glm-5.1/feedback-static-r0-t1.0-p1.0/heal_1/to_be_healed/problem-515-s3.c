#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int checkSubsetDivisibleByM(int arr[], int n, int m) {
    if (m == 1) {
        return 1;
    }
    if (n > m) {
        return 1;
    }
    int *dp = (int *)malloc(m * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    for (int i = 0; i < m; i++) {
        dp[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (dp[0]) {
            free(dp);
            return 1;
        }
        int *temp = (int *)malloc(m * sizeof(int));
        if (temp == NULL) {
            free(dp);
            return -1;
        }
        for (int j = 0; j < m; j++) {
            if (dp[j]) {
                if (temp[(j + arr[i]) % m] == 0) {
                    temp[(j + arr[i]) % m] = 1;
                }
            }
        }
        for (int j = 0; j < m; j++) {
            if (temp[j]) {
                dp[j] = 1;
            }
        }
        dp[arr[i] % m] = 1;
        free(temp);
    }
    int result = dp[0];
    free(dp);
    return result;
}

int main(void) {
    int arr[] = {3, 1, 5, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = 6;
    int res = checkSubsetDivisibleByM(arr, n, m);
    if (res == 1) {
        printf("Yes\n");
    } else if (res == 0) {
        printf("No\n");
    } else {
        printf("Memory allocation error\n");
        return 1;
    }
    return 0;
}