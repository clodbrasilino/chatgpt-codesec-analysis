#include <stdio.h>
#include <stdlib.h>

int longestBitonicSubsequence(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    int *lis = malloc(n * sizeof(int));
    int *lds = malloc(n * sizeof(int));

    if (lis == NULL || lds == NULL) {
        free(lis);
        free(lds);
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        lis[i] = 1;
    }

    for (size_t i = 1; i < n; i++) {
        for (size_t j = 0; j < i; j++) {
            if (arr[j] < arr[i] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        lds[i] = 1;
    }

    for (size_t i = n; i-- > 0;) {
        for (size_t j = n - 1; j > i; j--) {
            if (arr[j] < arr[i] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }

    int max_len = lis[0] + lds[0] - 1;

    for (size_t i = 1; i < n; i++) {
        int current_len = lis[i] + lds[i] - 1;
        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    free(lis);
    free(lds);

    return max_len;
}

int main(void) {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int result = longestBitonicSubsequence(arr, n);
    
    printf("%d\n", result);

    return 0;
}