#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int lis(int arr[], int n) {
    int *lis = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        lis[i] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }
    int max_lis = 0;
    for (int i = 0; i < n; i++) {
        if (max_lis < lis[i]) {
            max_lis = lis[i];
        }
    }
    free(lis);
    return max_lis;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as const array [constParameter]
 */
int lds(int arr[], int n) {
    int *lds = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        lds[i] = 1;
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }
    int max_lds = 0;
    for (int i = 0; i < n; i++) {
        if (max_lds < lds[i]) {
            max_lds = lds[i];
        }
    }
    free(lds);
    return max_lds;
}

int longestBitonicSubsequence(int arr[], int n) {
    int *dp = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dp[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        dp[i] = lis(arr, i + 1) + lds(arr + i, n - i) - 1;
    }
    int max_length = 0;
    for (int i = 0; i < n; i++) {
        if (max_length < dp[i]) {
            max_length = dp[i];
        }
    }
    free(dp);
    return max_length;
}

int main() {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of the longest bitonic subsequence is %d\n", longestBitonicSubsequence(arr, n));
    return 0;
}