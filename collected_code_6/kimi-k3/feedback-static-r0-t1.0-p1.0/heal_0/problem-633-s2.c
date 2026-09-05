#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_xor_pairs(const int *arr, size_t n)
{
    long long sum = 0;
    size_t i, j;

    if (arr == NULL || n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            sum += (long long)(arr[i] ^ arr[j]);
        }
    }

    return sum;
}

int main(void)
{
    size_t n, i;
    int *arr = NULL;
    long long result;
    int scan_result;

    printf("Enter number of elements: ");
    scan_result = scanf("%zu", &n);

    if (scan_result != 1 || n == 0) {
        fprintf(stderr, "Invalid input for number of elements\n");
        return EXIT_FAILURE;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Array size too large\n");
        return EXIT_FAILURE;
    }

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu integers:\n", n);
    for (i = 0; i < n; i++) {
        scan_result = scanf("%d", &arr[i]);
        if (scan_result != 1) {
            fprintf(stderr, "Invalid input for array element\n");
            free(arr);
            arr = NULL;
            return EXIT_FAILURE;
        }
    }

    result = sum_xor_pairs(arr, n);
    printf("Sum of XOR of all pairs: %lld\n", result);

    free(arr);
    arr = NULL;

    return EXIT_SUCCESS;
}