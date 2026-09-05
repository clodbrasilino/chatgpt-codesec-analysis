#include <stdio.h>
#include <stdlib.h>

long long product_non_repeated(const int *arr, size_t n)
{
    long long product = 1;
    size_t i, j;
    int found = 0;

    if (arr == NULL || n == 0) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        int count = 0;
        for (j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count == 1) {
            product *= arr[i];
            found = 1;
        }
    }

    return found ? product : 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 2, 4, 1, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result = product_non_repeated(arr, n);

    printf("Product of non-repeated elements: %lld\n", result);

    return 0;
}