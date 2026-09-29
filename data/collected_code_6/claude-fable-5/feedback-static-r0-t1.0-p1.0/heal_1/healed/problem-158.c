#include <stdio.h>
#include <stdlib.h>

long long min_operations_to_equal(const int *arr, size_t n, int k)
{
    size_t i;
    int max_val;
    long long total;

    if (arr == NULL || n == 0 || k <= 0) {
        return -1;
    }

    max_val = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    total = 0;
    for (i = 0; i < n; i++) {
        long long diff = (long long)max_val - (long long)arr[i];
        if (diff % k != 0) {
            return -1;
        }
        total += diff / k;
    }

    return total;
}

int main(void)
{
    int *arr;
    size_t n;
    size_t i;
    int k;
    long long result;

    printf("Enter number of elements: ");
    if (scanf("%zu", &n) != 1 || n == 0 || n > 1000000) {
        fprintf(stderr, "Invalid number of elements\n");
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

    printf("Enter k: ");
    if (scanf("%d", &k) != 1 || k <= 0) {
        fprintf(stderr, "Invalid value of k\n");
        free(arr);
        return EXIT_FAILURE;
    }

    result = min_operations_to_equal(arr, n, k);
    free(arr);

    if (result < 0) {
        printf("It is not possible to make all elements equal\n");
    } else {
        printf("Minimum operations required: %lld\n", result);
    }

    return EXIT_SUCCESS;
}