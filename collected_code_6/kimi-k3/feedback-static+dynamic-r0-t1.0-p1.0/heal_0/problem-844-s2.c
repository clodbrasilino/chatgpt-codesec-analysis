#include <stdio.h>
#include <stdlib.h>

int findKthElement(int *arr, int n, int k) {
    if (arr == NULL || k < 1 || k > n) {
        return -1;
    }
    return arr[k - 1];
}

int main(void) {
    int n, k, i;
    int *arr = NULL;
    int result;

    if (scanf("%d", &n) != 1 || n <= 0) {
        return EXIT_FAILURE;
    }

    arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            free(arr);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &k) != 1) {
        free(arr);
        return EXIT_FAILURE;
    }

    result = findKthElement(arr, n, k);
    if (result == -1) {
        free(arr);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    free(arr);

    return EXIT_SUCCESS;
}