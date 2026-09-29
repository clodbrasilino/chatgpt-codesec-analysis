#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_max_product_pair(const int *arr, size_t n, int *first, int *second)
{
    size_t i;
    int max1, max2, min1, min2;
    long long prod_max, prod_min;

    if (arr == NULL || first == NULL || second == NULL || n < 2U) {
        return -1;
    }

    if (arr[0] > arr[1]) {
        max1 = arr[0];
        max2 = arr[1];
        min1 = arr[1];
        min2 = arr[0];
    } else {
        max1 = arr[1];
        max2 = arr[0];
        min1 = arr[0];
        min2 = arr[1];
    }

    for (i = 2U; i < n; i++) {
        if (arr[i] > max1) {
            max2 = max1;
            max1 = arr[i];
        } else if (arr[i] > max2) {
            max2 = arr[i];
        }

        if (arr[i] < min1) {
            min2 = min1;
            min1 = arr[i];
        } else if (arr[i] < min2) {
            min2 = arr[i];
        }
    }

    prod_max = (long long)max1 * (long long)max2;
    prod_min = (long long)min1 * (long long)min2;

    if (prod_max >= prod_min) {
        *first = max1;
        *second = max2;
    } else {
        *first = min1;
        *second = min2;
    }

    return 0;
}

int main(void)
{
    int arr[] = { 1, 4, 3, 6, 7, 0, -9, -8 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int a = 0;
    int b = 0;

    if (find_max_product_pair(arr, n, &a, &b) != 0) {
        if (fprintf(stderr, "Error: invalid input or array too small\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Pair with highest product: %d and %d (product = %lld)\n",
               a, b, (long long)a * (long long)b) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}