#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int product_of_non_repeated(const int *arr, size_t n, long long *result)
{
    int *copy = NULL;
    long long product = 1;
    size_t i;

    if (arr == NULL || result == NULL || n == 0) {
        return -1;
    }

    copy = malloc(n * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    qsort(copy, n, sizeof(*copy), compare_ints);

    for (i = 0; i < n; i++) {
        if (i == 0 || copy[i] != copy[i - 1]) {
            product *= (long long)copy[i];
        }
    }

    free(copy);
    *result = product;
    return 0;
}

int main(void)
{
    int arr[] = {1, 1, 2, 3, 3, 4, 5, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result = 0;

    if (product_of_non_repeated(arr, n, &result) != 0) {
        fprintf(stderr, "Error computing product\n");
        return EXIT_FAILURE;
    }

    if (printf("Product of non-repeated elements: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}