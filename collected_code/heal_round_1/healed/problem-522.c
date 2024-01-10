#include <stdio.h>

int longestBitonicSubsequence(const int *arr, int n) {
    int i, j;
    int lis[n], lds[n];
    int max = 0;

    for (i = 0; i < n; i++) {
        lis[i] = 1;
        lds[i] = 1;
    }

    for (i = 1; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (*(arr + i) > *(arr + j) && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    for (i = n - 2; i >= 0; i--) {
        for (j = n - 1; j > i; j--) {
            if (*(arr + i) > *(arr + j) && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (max < lis[i] + lds[i] - 1) {
            max = lis[i] + lds[i] - 1;
        }
    }

    return max;
}

int main() {
    const int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("The length of the longest bitonic subsequence is: %d\n", longestBitonicSubsequence(arr, n));

    return 0;
}