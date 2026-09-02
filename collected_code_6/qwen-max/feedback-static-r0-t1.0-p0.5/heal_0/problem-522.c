#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestBitonicSubsequence(int arr[], int n) {
    int *increasing = (int *)malloc(n * sizeof(int));
    int *decreasing = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        increasing[i] = 1;
        decreasing[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && increasing[i] < increasing[j] + 1) {
                increasing[i] = increasing[j] + 1;
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && decreasing[i] < decreasing[j] + 1) {
                decreasing[i] = decreasing[j] + 1;
            }
        }
    }

    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        if (maxLength < increasing[i] + decreasing[i] - 1) {
            maxLength = increasing[i] + decreasing[i] - 1;
        }
    }

    free(increasing);
    free(decreasing);

    return maxLength;
}

int main() {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Length of the longest bitonic subsequence is %d\n", longestBitonicSubsequence(arr, n));
    return 0;
}