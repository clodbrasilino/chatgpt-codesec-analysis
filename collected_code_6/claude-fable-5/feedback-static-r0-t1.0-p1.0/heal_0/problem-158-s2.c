#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long min_operations(const int *arr, size_t n);

long long min_operations(const int *arr, size_t n)
{
    long long sum = 0;
    int min_val = INT_MAX;
    size_t i;

    if (arr == NULL || n == 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        sum += (long long)arr[i];
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    return sum - ((long long)min_val * (long long)n);
}

int main(void)
{
    size_t n = 0;
    size_t i;
    int *arr = NULL;
    long long result;

    printf("Enter number of elements: ");
    if (scanf("%zu", &n) != 1 || n == 0 || n > 1000000) {
        fprintf(stderr, "Invalid input for number of elements\n");
        return EXIT_FAILURE;
    }

    arr = malloc(n * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu elements: ", n);
    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid element input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    result = min_operations(arr, n);
    if (result < 0) {
        fprintf(stderr, "Computation error\n");
        free(arr);
        return EXIT_FAILURE;
    }

    printf("Number of operations required: %lld\n", result);

    free(arr);
    return EXIT_SUCCESS;
}