#include <stdio.h>
#include <stdlib.h>

int longestBitonicSubsequence(int* arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int* lis = (int*)malloc(n * sizeof(int));
    if (lis == NULL) {
        return 0;
    }

    int* lds = (int*)malloc(n * sizeof(int));
    if (lds == NULL) {
        free(lis);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        lis[i] = 1;
        lds[i] = 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }

    int max_len = 0;
    for (int i = 0; i < n; i++) {
        if (lis[i] + lds[i] - 1 > max_len) {
            max_len = lis[i] + lds[i] - 1;
        }
    }

    free(lis);
    free(lds);

    return max_len;
}

int main(void) {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = longestBitonicSubsequence(arr, n);
    printf("%d\n", result);

    return 0;
}