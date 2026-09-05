#include <stdio.h>
#include <stddef.h>
#include <limits.h>

int findMaxProductPair(const int arr[], size_t size, int *first, int *second)
{
    size_t i;
    int max1;
    int max2;
    int min1;
    int min2;
    long long productMax;
    long long productMin;

    if (arr == NULL || first == NULL || second == NULL || size < 2U) {
        return -1;
    }

    max1 = INT_MIN;
    max2 = INT_MIN;
    min1 = INT_MAX;
    min2 = INT_MAX;

    for (i = 0U; i < size; i++) {
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

    productMax = (long long)max1 * (long long)max2;
    productMin = (long long)min1 * (long long)min2;

    if (productMax >= productMin) {
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
    int arr[] = {1, 4, 3, 6, 7, 0, -5, -8};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int first = 0;
    int second = 0;

    if (findMaxProductPair(arr, size, &first, &second) == 0) {
        printf("Pair with highest product: %d and %d (product = %lld)\n",
               first, second, (long long)first * (long long)second);
    } else {
        fprintf(stderr, "Error: unable to find a valid pair\n");
        return 1;
    }

    return 0;
}