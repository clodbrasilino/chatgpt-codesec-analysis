#include <stdio.h>
#include <stdlib.h>

long long product_of_non_repeated(const int *arr, size_t n)
{
    long long product = 1;
    size_t i;
    size_t j;
    int seen;

    if (arr == NULL || n == 0) {
        return 1;
    }

    for (i = 0; i < n; i++) {
        seen = 0;
        for (j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                seen = 1;
                break;
            }
        }
        if (seen == 0) {
            product *= (long long)arr[i];
        }
    }

    return product;
}

int main(void)
{
    int arr[] = {1, 1, 2, 3, 4, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    result = product_of_non_repeated(arr, n);

    if (printf("Product of non-repeated elements: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}