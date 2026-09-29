#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int minJumps(int *arr, int n) {
    if (n <= 0) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    if (arr[0] == 0) {
        return -1;
    }
    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return -1;
    }
    for (int i = 1; i < n; i++) {
        dp[i] = INT_MAX;
    }
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] == INT_MAX) {
            continue;
        }
        for (int j = i + 1; j < n && j <= i + arr[i]; j++) {
            if (dp[i] + 1 < dp[j]) {
                dp[j] = dp[i] + 1;
            }
        }
    }
    int result = dp[n - 1] == INT_MAX ? -1 : dp[n - 1];
    free(dp);
    return result;
}

int main() {
    int arr1[] = {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", minJumps(arr1, n1));
    int arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", minJumps(arr2, n2));
    int arr3[] = {2, 3, 1, 1, 4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", minJumps(arr3, n3));
    int arr4[] = {1, 0, 3};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    printf("%d\n", minJumps(arr4, n4));
    int arr5[] = {0};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    printf("%d\n", minJumps(arr5, n5));
    return 0;
}