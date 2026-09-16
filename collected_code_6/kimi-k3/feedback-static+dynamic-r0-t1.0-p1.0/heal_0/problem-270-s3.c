#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int sum_even_at_even_positions(const int *arr, size_t size, long *result)
{
    size_t i;
    long sum;

    if (arr == NULL || result == NULL) {
        return -1;
    }

    if (size == 0) {
        *result = 0;
        return 0;
    }

    sum = 0;
    for (i = 0; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            if (sum > LONG_MAX - arr[i]) {
                return -2;
            }
            sum += arr[i];
        }
    }

    *result = sum;
    return 0;
}

int main(void)
{
    int *arr;
    size_t n;
    size_t i;
    long result;
    int status;
    int scan_result;

    printf("Enter the number of elements: ");
    scan_result = scanf("%zu", &n);
    
    if (scan_result != 1 || n == 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Size too large\n");
        return EXIT_FAILURE;
    }

    arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu integers: ", n);
    for (i = 0; i < n; i++) {
        scan_result = scanf("%d", &arr[i]);
        if (scan_result != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            arr = NULL;
            return EXIT_FAILURE;
        }
    }

    status = sum_even_at_even_positions(arr, n, &result);
    
    if (status == 0) {
        printf("Sum of even numbers at even positions: %ld\n", result);
    } else if (status == -2) {
        fprintf(stderr, "Integer overflow occurred\n");
    } else {
        fprintf(stderr, "Error processing array\n");
    }

    free(arr);
    arr = NULL;

    return (status == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}