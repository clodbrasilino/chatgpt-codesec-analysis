#include <stdio.h>
#include <stdlib.h>

int find_largest_divisible_subset(const int* arr, int n) {
    if (n == 0) {
        return 0;
    }

    int* dp = (int*)malloc(n * sizeof(int));
    if (dp == NULL) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    int max_size = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] % arr[j] == 0 || arr[j] % arr[i] == 0) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > max_size) {
            max_size = dp[i];
        }
    }

    free(dp);
    return max_size;
}

int main() {
    int arr1[] = {1, 2, 3, 6, 8};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_largest_divisible_subset(arr1, n1);
    printf("%d\n", result1);

    int arr2[] = {5, 10, 20, 25, 50};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_largest_divisible_subset(arr2, n2);
    printf("%d\n", result2);

    int arr3[] = {3, 5, 7, 11};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = find_largest_divisible_subset(arr3, n3);
    printf("%d\n", result3);

    return 0;
}