#include <stdio.h>
#include <stdlib.h>

int longestBitonicSubsequence(const int arr[], int n) {
    int *increasing = (int *)malloc(n * sizeof(int));
    int *decreasing = (int *)malloc(n * sizeof(int));
    int i, j, max_length = 0;

    for (i = 0; i < n; i++) {
        increasing[i] = 1;
        decreasing[i] = 1;
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (arr[i] > arr[j] && increasing[i] < increasing[j] + 1) {
                increasing[i] = increasing[j] + 1;
            }
        }
    }

    for (i = n - 2; i >= 0; i--) {
        for (j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && decreasing[i] < decreasing[j] + 1) {
                decreasing[i] = decreasing[j] + 1;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (max_length < increasing[i] + decreasing[i] - 1) {
            max_length = increasing[i] + decreasing[i] - 1;
        }
    }

    free(increasing);
    free(decreasing);

    return max_length;
}

int main() {
    const int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = longestBitonicSubsequence(arr, n);
    printf("Length of Longest Bitonic Subsequence is %d\n", result);
    return 0;
}