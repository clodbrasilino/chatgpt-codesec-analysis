#include <stdio.h>
#include <stdlib.h>

int find_longest_bitonic_subsequence(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    int *lis = (int *)malloc(n * sizeof(int));
    if (lis == NULL) {
        return -1;
    }

    int *lds = (int *)malloc(n * sizeof(int));
    if (lds == NULL) {
        free(lis);
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        lis[i] = 1;
        for (size_t j = 0; j < i; j++) {
            if (arr[i] > arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    for (size_t i = n; i-- > 0; ) {
        lds[i] = 1;
        for (size_t j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }

    int max_len = 0;
    for (size_t i = 0; i < n; i++) {
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
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int result = find_longest_bitonic_subsequence(arr, n);
    
    if (result < 0) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Length of Longest Bitonic Subsequence: %d\n", result);

    return EXIT_SUCCESS;
}