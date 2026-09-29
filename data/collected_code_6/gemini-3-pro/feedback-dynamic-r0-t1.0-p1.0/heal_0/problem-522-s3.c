#include <stdio.h>
#include <stdlib.h>

int longestBitonicSubsequence(int* arr, int n) {
    if (n <= 0) {
        return 0;
    }

    int* inc = (int*)malloc(n * sizeof(int));
    if (inc == NULL) {
        return 0;
    }

    int* dec = (int*)malloc(n * sizeof(int));
    if (dec == NULL) {
        free(inc);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        inc[i] = 1;
        dec[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && inc[i] < inc[j] + 1) {
                inc[i] = inc[j] + 1;
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && dec[i] < dec[j] + 1) {
                dec[i] = dec[j] + 1;
            }
        }
    }

    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        if (inc[i] + dec[i] - 1 > maxLength) {
            maxLength = inc[i] + dec[i] - 1;
        }
    }

    free(inc);
    free(dec);

    return maxLength;
}

int main(void) {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = longestBitonicSubsequence(arr, n);
    printf("%d\n", result);

    return 0;
}