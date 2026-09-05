#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findLargestDivisibleSubset(int *arr, int n) {
    if (n == 0) {
        return 0;
    }

    int *dp = (int *)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    qsort(arr, n, sizeof(int), compare);

    int max_len = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] % arr[j] == 0) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }

    free(dp);
    return max_len;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = findLargestDivisibleSubset(arr1, n1);
    printf("%d\n", result1);

    int arr2[] = {1, 2, 4, 8};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = findLargestDivisibleSubset(arr2, n2);
    printf("%d\n", result2);

    int arr3[] = {5, 10, 20, 25, 50};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = findLargestDivisibleSubset(arr3, n3);
    printf("%d\n", result3);

    return 0;
}