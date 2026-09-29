#include <stdio.h>
#include <stdlib.h>

int longest_bitonic_subsequence(const int arr[], int n)
{
    int *lis;
    int *lds;
    int max_len;
    int i;
    int j;

    if (arr == NULL || n <= 0) {
        return 0;
    }

    lis = (int *)malloc((size_t)n * sizeof(int));
    if (lis == NULL) {
        return -1;
    }

    lds = (int *)malloc((size_t)n * sizeof(int));
    if (lds == NULL) {
        free(lis);
        lis = NULL;
        return -1;
    }

    for (i = 0; i < n; i++) {
        lis[i] = 1;
        for (j = 0; j < i; j++) {
            if (arr[j] < arr[i] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    for (i = n - 1; i >= 0; i--) {
        lds[i] = 1;
        for (j = n - 1; j > i; j--) {
            if (arr[j] < arr[i] && lds[i] < lds[j] + 1) {
                lds[i] = lds[j] + 1;
            }
        }
    }

    max_len = lis[0] + lds[0] - 1;
    for (i = 1; i < n; i++) {
        if (max_len < lis[i] + lds[i] - 1) {
            max_len = lis[i] + lds[i] - 1;
        }
    }

    free(lis);
    lis = NULL;
    free(lds);
    lds = NULL;

    return max_len;
}

int main(void)
{
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int result;

    result = longest_bitonic_subsequence(arr, n);
    if (result < 0) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Length of longest bitonic subsequence: %d\n", result);

    return EXIT_SUCCESS;
}